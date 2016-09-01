//
// Created by root on 31/8/16.
//

#ifndef COL333ASSIGNMENT1_SEARCH_H
#define COL333ASSIGNMENT1_SEARCH_H

#include "Problem.h"
#include "node.h"

typedef std::priority_queue<State, std::vector<State>, CompareState> vss;

class Search {

public:
    // search functions

    static void localGreedySearch(Problem* problem, int numRestarts);

    // completeness checks

    static bool isCompleteLocalMaximum(std::vector<State> oldfringe, std::vector<State> newfringe);

private:
    static vss generalSearch(Problem *problem, int iterationLimit, int fringeSize, bool isRandomInitialize, int expanderCode,
                             int completenessCode);
};

#endif //COL333ASSIGNMENT1_SEARCH_H
