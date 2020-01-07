#include "strategy.hpp"

Strategy::Strategy(int term, int max) {
    fitness = 0;
    evolutionTerm = term;
    maxPossibleUtility = max;
}

double Strategy::getFitness() const {
    return fitness;
}

void Strategy::calculateFitness() {
    double sum = 0;
    for (auto const& ele : utilities) {
        sum += ele;
    }
    fitness = (sum / evolutionTerm) / maxPossibleUtility;  // normalize the fitness value
}

void Strategy::addUtility(int value) {
    utilities.push_back(value);
}

void Strategy::addDecision(bool decision) {
    decisionVector.push_back(decision);
}
void Strategy::clearUtilities() {
    utilities.clear();
}