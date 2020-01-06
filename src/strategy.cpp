#include "strategy.hpp"
#include <cstdlib>


Strategy::Strategy(const vector<bool>& decisions, int evolutionTerm, int max) {
    decisionVector = decisions;
    fitness = 0;
    utilities = (int*)calloc(evolutionTerm, sizeof(int));
    this->evolutionTerm = evolutionTerm;
    maxPossibleUtility = max;
}

Strategy::~Strategy() {
    free(utilities);
}

double Strategy::getFitness() const {
    return fitness;
}

void Strategy::calculateFitness() {
    double sum = 0;
    for (int i = 0; i < evolutionTerm; ++i) {
        sum += utilities[i];
    }
    fitness = (sum / evolutionTerm) / maxPossibleUtility;  // normalize the fitness value
}