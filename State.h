//
// Created by root on 31/8/16.
//

#ifndef COL333ASSIGNMENT1_STATE_H
#define COL333ASSIGNMENT1_STATE_H

#include <vector>
#include "node.h"

class State {
private:
    std::vector<int> bidNumbers;
    double cost;
    int numConflicts;

public:
    State(std::vector<int> bidNumbers, double cost, int numConflicts);

    std::vector<int> getBidNumbers();

    void setBidNumbers(std::vector<int> bidNumbers);

    int getConflicts();

    void setConflicts(int numConflicts);

    double getCost() const;

    bool isValid();

    bool operator==(const State &state);
};

class CompareState {
public:
    bool operator()(State state1, State state2) {
        return (state1.getCost() < state2.getCost());
    }
};

#endif //COL333ASSIGNMENT1_STATE_H
