#include "State.h"

State::State(std::vector<int> bidNumbers, double cost, int numConflicts) {

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

double State::getCost() {
    return this->cost;
}




