//
// Created by root on 31/8/16.
//

#ifndef COL333ASSIGNMENT1_SEARCH_H
#define COL333ASSIGNMENT1_SEARCH_H

#include "Problem.h"
#include "node.h"

class Search
{
    // search functions

    void localGreedySearch(Problem problem);

    // completeness checks


    void generalSearch(Problem problem, int iterationLimit, int fringeSize, bool isRandomInitialize, int expanderCode, int completenessCode);
};

#endif //COL333ASSIGNMENT1_SEARCH_H
