//
// Created by root on 31/8/16.
//

#ifndef COL333ASSIGNMENT1_PROBLEM_H
#define COL333ASSIGNMENT1_PROBLEM_H

#include <vector>
#include <queue>
#include "State.h"
#include "node.h"

class Problem
{
private:
    State state = State(std::vector<int>(), 0, 0);
    State initialState = State(std::vector<int>(), 0, 0);
    std::priority_queue<State, std::vector<State>, CompareState> validStateStore;
    std::vector<struct node> problemData[];
    int maxbids[];

public:
    Problem(struct node* bidsArray[], int numBids);
    State generateRandomState();
    void setInitialState(State initialState);
    std::vector<State> getNeighbours(State currentState);
    std::vector<State> fringeExpander(std::vector<State> fringe, int fringeSize, int expanderCode);

    // expanders
};

#endif //COL333ASSIGNMENT1_PROBLEM_H
