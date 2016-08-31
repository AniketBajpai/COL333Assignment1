#include "Problem.h"

using namespace std;

Problem::Problem(struct node bidsArray[], int numBids, int numCompanies, int numRegions) {
    // get problem data and company size from bidsArray

    this->problemData = new vector<struct node>[numCompanies];
    this->maxBids = new int[numCompanies];
    this->numCompanies = numCompanies;
    this->numRegions = numRegions;
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

State Problem::generateRandomState() {
    vector<int> bidNos;
    for (int i = 0; i < this->numCompanies; i++) {
        int r = (rand()) % (this->maxBids[i] + 1);
        bidNos.push_back(r);
    }

    double totalCost = getStateCost(bidNos);
    int totalConflicts = getStateConflicts(bidNos);
    return State(bidNos, totalCost, totalConflicts);
}

void Problem::setInitialState(State initialState) {

}

std::vector<State> Problem::getNeighbours(State currentState) {
    return std::vector<State>();
}

std::vector<State> Problem::fringeExpander(std::vector<State> fringe, int fringeSize, int expanderCode) {
    return vector<State>();
}

