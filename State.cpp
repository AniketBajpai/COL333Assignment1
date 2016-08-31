#include "State.h"

State::State(std::vector<int> bidNumbers, int cost, int numConflicts) {

}

std::vector<int> State::getBidNumbers() {
    return this->bidNumbers;
}

void State::setBidNumbers(std::vector<int> bidNumbers) {

}

int State::getConflicts() {
    return this->numConflicts;
}

void State::setConflicts(int numConflicts) {
    this->numConflicts = numConflicts;
}

int State::getCost() {
    return this->cost;
}




