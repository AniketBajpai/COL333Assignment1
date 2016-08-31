//
// Created by root on 31/8/16.
//

#ifndef COL333ASSIGNMENT1_PROBLEM_H
#define COL333ASSIGNMENT1_PROBLEM_H

#include <vector>
#include <queue>
#include <random>
#include "State.h"
#include "node.h"

class Problem {
private:
    State state = State(std::vector<int>(), 0, 0);
    State initialState = State(std::vector<int>(), 0, 0);
    std::priority_queue<State, std::vector<State>, CompareState> validStateStore;
    std::vector<struct node> *problemData;
    int *maxBids;
    int numCompanies;
    int numRegions;

    double getStateCost(std::vector<int> bidNos);

    int getStateConflicts(std::vector<int> bidNos);

public:
    Problem(struct node bidsArray[], int numBids, int numCompanies, int numRegions);

    State getStateFromBidNumbers(std::vector<int> bidNos);

    State generateRandomState();

    void setInitialState(State initialState);

    std::vector<State> getNeighbours(State currentState);

    std::vector<State> fringeExpander(std::vector<State> fringe, int fringeSize, int expanderCode);

    // expanders
};

#endif //COL333ASSIGNMENT1_PROBLEM_H
