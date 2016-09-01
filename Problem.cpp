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
        this->maxBids[i] = (this->problemData[i]).size() + 1;
    }
}

State Problem::getInitialState() {
    return this->initialState;
}

vss Problem::getValidStore(){
    return this->validStateStore;
}

void Problem::clearValidStore(){
    this->validStateStore = vss();
}

double Problem::getStateCost(vector<int> bidNos) {
    double totalCost = 0;
    for (int i = 0; i < this->numCompanies; i++) {
        int curBidNumber = bidNos[i];
        double curcost = this->problemData[i][curBidNumber].price;
        totalCost += curcost;
    }
    return totalCost;
}

int Problem::getStateConflicts(vector<int> bidNos) {
    vector<int> conflictArray;
    conflictArray.resize(this->numRegions, 0);
    int totalConflicts = 0;
    for (int i = 0; i < this->numCompanies; i++) {
        int curBidNumber = bidNos[i];
        int *curRegions = this->problemData[i][curBidNumber].region;
        int curRegionsSize = this->problemData[i][curBidNumber].norc;
        for (int j = 0; j < curRegionsSize; j++) {
            if (conflictArray[curRegions[j]] != 0) {
                totalConflicts++;
            }
            else {
                conflictArray[curRegions[j]] = 1;
            }
        }
        // totalCost += curcost;
    }
    return totalConflicts;
}

State Problem::getStateFromBidNumbers(vector<int> bidNos){
    double totalCost = getStateCost(bidNos);
    int totalConflicts = getStateConflicts(bidNos);
    return State(bidNos, totalCost, totalConflicts);
}

State Problem::generateRandomState() {
    vector<int> bidNos;
    for (int i = 0; i < this->numCompanies; i++) {
        int r = (rand()) % (this->maxBids[i] + 1);
        bidNos.push_back(r);
    }

    State state = getStateFromBidNumbers(bidNos);
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
        int currentBid =bidNumbers[i];
        for (int j = 0; j < this->maxBids[i]; ++j) {
            if(j!=currentBid){
                vector<int> newBidNumbers(bidNumbers);
                newBidNumbers[i] = j;
                State neighbourState = getStateFromBidNumbers(newBidNumbers);
                neighbours.push_back(neighbourState);
            }
        }
    }

    return neighbours;
}

bool compareStateDesc(State state1, State state2){
    return state1.getCost() > state2.getCost();
}

vector<State> Problem::localGreedyExpander(vector<State> fringe, int fringeSize){
    sort(fringe.begin(), fringe.end(), compareStateDesc);
    // Resize fringe greedily
    fringe.resize(fringeSize, generateRandomState());   // fill fringe with random states if size less than fringeSize
    return fringe;
}

vector<State> Problem::fringeExpander(vector<State> fringe, int fringeSize, int expanderCode) {
    // Initialize new fringe with old fringe
    vector<State> newfringe(fringe);

    // TODO: improve method to form new fringe without using enormous space each time
    // Algorithm has much less running time for fringeSize=1 -> Re-implement
    for (auto it=fringe.begin(); it<fringe.end(); it++){
        vector<State> neighbours = getNeighbours(*it);
        newfringe.insert(newfringe.end(), neighbours.begin(), neighbours.end());
    }

    // Update validStateStore if valid state found among neighbours
    for (auto it=newfringe.begin(); it<newfringe.end(); it++){
        State state = *it;
        if(state.isValid()){
            validStateStore.push(state);
        }
        if(validStateStore.size() > validStoreSize){
            validStateStore.pop();
        }
    }

    // Carry out operation according to expanderCode
    /*
     * Codes for expander functions
     * 0 : greedy expander
     */
    vector<State> expandedfringe;
    switch(expanderCode){
        case 0:
            expandedfringe = localGreedyExpander(newfringe, fringeSize);
            break;

        default:
            expandedfringe = localGreedyExpander(newfringe, fringeSize);
            break;
    }

    return expandedfringe;
}




