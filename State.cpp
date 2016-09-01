#include "State.h"

State::State(std::vector<int> bidNumbers, double cost, int numConflicts) {
    this->bidNumbers = bidNumbers;
    this->cost = cost;
    this->numConflicts = numConflicts;
}

std::vector<int> State::getBidNumbers() {
    return this->bidNumbers;
}

void State::setBidNumbers(std::vector<int> bidNumbers) {
    this->bidNumbers = bidNumbers;
}

int State::getConflicts() {
    return this->numConflicts;
}

void State::setConflicts(int numConflicts) {
    this->numConflicts = numConflicts;
}

double State::getCost() const {
    return this->cost;
}

bool State::isValid(){
    return (this->getConflicts() == 0);
}

bool State::operator==(const State& state){
    return (this->cost == state.getCost());
}




