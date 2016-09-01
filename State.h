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

    int getConflicts() const;

    void setConflicts(int numConflicts);

    double getCost() const;

    double getFitness() const;

    bool isValid();

    bool operator==(const State &state) const;
};

class CompareState {
public:
    bool operator()(State state1, State state2) {
        return (state1.getFitness() < state2.getFitness());
    }
};

#endif //COL333ASSIGNMENT1_STATE_H
