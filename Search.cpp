#include "Search.h"

using namespace std;

void Search::localGreedySearch(Problem* problem, int numTries) {
    int iterationLimit = 10000;
    int fringeSize = 1;
    bool randomInitialize = true;
    int greedyExpanderCode = 0;   // local greedy expansion
    int localMaxCompletenessCode = 0;   // terminate if local maximum

    vss GlobalValidStates;  // stores best valid states among all tries
    int maxStoredStates = 100;

    for (int i = 0; i < numTries; ++i) {
        vss validStore = generalSearch(problem, iterationLimit, fringeSize, randomInitialize, greedyExpanderCode,
                                       localMaxCompletenessCode);
        // Update global state store
        while (!validStore.empty()) {
            GlobalValidStates.push(validStore.top());
            validStore.pop();
            if (GlobalValidStates.size() > maxStoredStates) {
                GlobalValidStates.pop();
            }
        }
    }

    if(GlobalValidStates.size()>0){
        State bestState = GlobalValidStates.top();
        string bestStateString = problem->getStringFromState(bestState);
        cout<<bestStateString<<endl;
    }
    else {
        cout<<"No valid states found"<<endl;
    }
}

bool Search::isCompleteLocalMaximum(std::vector<State> oldfringe, std::vector<State> newfringe) {
    bool checkEqual = equal(newfringe.begin(), newfringe.end(), oldfringe.begin());
    return checkEqual;
}

// General algorithm at core of all search algorithms
vss Search::generalSearch(Problem *problem, int iterationLimit, int fringeSize, bool isRandomInitialize,
                          int expanderCode, int completenessCode) {

    vector<State> fringe;
    vector<State> newfringe;
    problem->clearValidStore();

    // Initialize fringe
    if (isRandomInitialize) {
        for (int i = 0; i < fringeSize; ++i) {
            State randomState = problem->generateRandomState();
            fringe.push_back(randomState);
        }
    }
    else {
        fringe.push_back(problem->getInitialState());
        for (int i = 0; i < fringeSize - 1; ++i) {
            State randomState = problem->generateRandomState();
            fringe.push_back(randomState);
        }
    }

    int iterationCount = 0;
    bool run = true;

    while (run) {
        newfringe = problem->fringeExpander(fringe, fringeSize, 0);

        // Check if search is complete
        if (iterationCount >= iterationLimit) {
            run = false;
            cout << "Exceeded max iterations" << endl;
            break;
        }

        cout<<"Iteration: "<<iterationCount<<endl;
        cout<<"Best state: "<<problem->getStringFromState(newfringe[0])<<endl;

        bool isComplete;

        /*
         * Codes for completeness checking functions
         * 0 : terminate if local maximum found
         */
        switch (completenessCode) {
            case 0:
                isComplete = isCompleteLocalMaximum(fringe, newfringe);
                break;
            default:
                isComplete = isCompleteLocalMaximum(fringe, newfringe);
        }
        if (isComplete) {
            run = false;
            cout << "Reached Local maxima" << endl;
            break;
        }

        fringe = newfringe;
        iterationCount++;
    }

    return problem->getValidStore();

}

