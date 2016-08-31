#include "Problem.h"
using namespace std;

Problem::Problem(struct node* bidsArray[], int numBids) {
    // get problem data and company size from bidsArray
    int C = 0;

}


State Problem::generateRandomState() {
    return State(vector<int>(), 0, 0);
}

void Problem::setInitialState(State initialState) {

}

std::vector<State> Problem::getNeighbours(State currentState) {
    return std::vector<State>();
}

std::vector<State> Problem::fringeExpander(std::vector<State> fringe, int fringeSize, int expanderCode) {
    return vector<State>();
}

