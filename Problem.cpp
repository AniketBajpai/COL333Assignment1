#include "Problem.h"

using namespace std;

Problem::Problem(struct node bidsArray[], int numBids, int numCompanies, int numRegions) {
    // get problem data and company size from bidsArray

    this->problemData = new vector<struct node>[numCompanies];
    this->maxBids = new int[numCompanies];
    this->numCompanies = numCompanies;
    this->numRegions = numRegions;
    this->validStoreSize = 100;

    //Add no bid node for each company
    for (int i = 0; i < numCompanies; i++) {
        struct node emptyNode;
        emptyNode.cid = i;
        emptyNode.price = 0;
        emptyNode.norc = 0;
        this->problemData[i].push_back(emptyNode);
    }

    //Arrange input data
    for (int i = 0; i < numBids; i++) {
        int cid = bidsArray[i].cid;
        (this->problemData[cid]).push_back(bidsArray[i]);
    }

    //Initialize maxBids array for all companies
    for (int i = 0; i < numCompanies; i++) {
        this->maxBids[i] = (this->problemData[i]).size();
    }
}

State Problem::getInitialState() {
    return this->initialState;
}

int* Problem::getMaxBids() {
    return this->maxBids;
}

vss Problem::getValidStore() {
    return this->validStateStore;
}

void Problem::clearValidStore() {
    this->validStateStore = vss();
}

double Problem::getStateCost(vector<int> bidNos) {
    double totalCost = 0;
    for (int i = 0; i < this->numCompanies; i++) {
        int curBidNumber = bidNos[i];
        double curcost = this->problemData[i][curBidNumber].price;
        totalCost += curcost;
    }
    return (totalCost);// - 1000000*getStateConflicts(bidNos));
}

int Problem::getStateConflicts(vector<int> bidNos) {
    vector<int> conflictArray(this->numRegions, 0);
    int totalConflicts = 0;
    for (int i = 0; i < this->numCompanies; i++) {
        int curBidNumber = bidNos[i];
        // cout<<"Current bid no.: "<<curBidNumber<<endl;
        int *curRegions = this->problemData[i][curBidNumber].region;
        int curRegionsSize = this->problemData[i][curBidNumber].norc;
        // cout<<"Region size: "<<curRegionsSize<<endl;
        for (int j = 0; j < curRegionsSize; j++) {
            if (conflictArray[curRegions[j]] != 0) {
                totalConflicts++;
            }
            else {
                conflictArray[curRegions[j]] = 1;
            }
        }
    }
    // cout<<"Conflicts found: "<<totalConflicts<<endl;
    return totalConflicts;
}

State Problem::getStateFromBidNumbers(vector<int> bidNos) {
    // cout<<"Getting state"<<endl;
    double totalCost = getStateCost(bidNos);
    // cout<<"Cost: "<<to_string(totalCost)<<", ";
    int totalConflicts = getStateConflicts(bidNos);
    // cout<<"Conflicts: "<<totalConflicts<<endl;
    return State(bidNos, totalCost, totalConflicts);
}

State Problem::generateRandomState() {
    vector<int> bidNos;
    for (int i = 0; i < this->numCompanies; i++) {
        int r = (rand()) % (this->maxBids[i]);
        bidNos.push_back(r);
    }

    State state = getStateFromBidNumbers(bidNos);
    this->initialState = state;
    return state;
}


void Problem::setInitialState(State initialState) {
    this->initialState = initialState;
}

vector<State> Problem::getNeighbours(State currentState) {
    vector<int> bidNumbers = currentState.getBidNumbers();
    vector<State> neighbours;

    // Push all adjacent neighbours to vector
    // TODO: find way to do operations without using O(B*C) space
    for (int i = 0; i < this->numCompanies; ++i) {
        int currentBid = bidNumbers[i];
        for (int j = 0; j < this->maxBids[i]; ++j) {
            if (j != currentBid) {
                vector<int> newBidNumbers(bidNumbers);
                newBidNumbers[i] = j;
                State neighbourState = getStateFromBidNumbers(newBidNumbers);
                neighbours.push_back(neighbourState);
            }
        }
    }

    return neighbours;
}

bool compareStateDesc(State state1, State state2) {
    return state1.getFitness() > state2.getFitness();
}

vector<State> Problem::localGreedyExpander(vector<State> fringe, int fringeSize) {
    sort(fringe.begin(), fringe.end(), compareStateDesc);
    // Resize fringe greedily
    fringe.resize(fringeSize, generateRandomState());   // fill fringe with random states if size less than fringeSize
    return fringe;
}

std::string Problem::getStringFromState(State state) {
    string stateString = "{";
    vector<int> bidNos = state.getBidNumbers();
    for (int i = 0; i < bidNos.size(); ++i) {
        int curBidNumber = bidNos[i];
        if(curBidNumber>0){
            string currString = "[";
            int *curRegions = this->problemData[i][curBidNumber].region;
            int curRegionsSize = this->problemData[i][curBidNumber].norc;
            for (int j = 0; j < curRegionsSize; j++) {
                currString.append(to_string(curRegions[j]) + " ");
            }
            currString.replace(currString.length()-1, 1, "]");
            stateString.append("(").append(to_string(i)).append(",").append(" "+to_string(curBidNumber)+": ").append(currString).append(")");
        }
    }
    stateString.append("}").append(to_string(getStateCost(state.getBidNumbers())));
    return stateString;
}


vector<State> Problem::fringeExpander(vector<State> fringe, int fringeSize, int expanderCode) {
    // Initialize new fringe with old fringe
    vector<State> newfringe(fringe);
    cout<<"Expanding fringe"<<endl;

    // TODO: improve method to form new fringe without using enormous space each time
    // Algorithm has much less running time for fringeSize=1 -> Re-implement
    for (auto it = fringe.begin(); it < fringe.end(); it++) {
        vector<State> neighbours = getNeighbours(*it);
        newfringe.insert(newfringe.end(), neighbours.begin(), neighbours.end());
    }

    // Update validStateStore if valid state found among neighbours
    for (auto it = newfringe.begin(); it < newfringe.end(); it++) {
        State state = *it;
        if (state.isValid()) {
            validStateStore.push(state);
        }
        if (validStateStore.size() > validStoreSize) {
            // validStateStore.pop();                  //Question: Won't this remove the best states???????
        }
    }

    // Carry out operation according to expanderCode
    /*
     * Codes for expander functions
     * 0 : greedy expander
     */
    vector<State> expandedfringe;
    switch (expanderCode) {
        case 0:
            expandedfringe = localGreedyExpander(newfringe, fringeSize);
            break;

        default:
            expandedfringe = localGreedyExpander(newfringe, fringeSize);
            break;
    }

    return expandedfringe;
}




