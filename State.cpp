#include "State.h"

// TODO: Suitably choose W
double W = 1000;

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

int State::getConflicts() const {
    return this->numConflicts;
}

void State::setConflicts(int numConflicts) {
    this->numConflicts = numConflicts;
}

double State::getCost() const {
    return this->cost;
}

double State::getFitness() const {
    return (getCost() - W * getConflicts());
}

bool State::isValid() {
    return (this->getConflicts() == 0);
}

bool State::operator==(const State &state) const {
    return (this->getFitness() == state.getFitness());
}






