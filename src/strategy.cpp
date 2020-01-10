#include "strategy.hpp"

Strategy::Strategy(int term, int max) {
    fitness = 0;
    evolutionTerm = term;
    maxPossibleUtility = max;
}

vector<bool> Strategy::getDecision() const {
    return decisionVector;
}

double Strategy::getFitness() const {
    return fitness;
}

void Strategy::calculateFitness() { // OK
    if (!utilities.empty()) {
        double sum = 0;
        for (auto const &ele : utilities) {
            sum += ele;
        }
        fitness = (sum / evolutionTerm) / maxPossibleUtility;  // normalize the fitness value
    }
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

void Strategy::setDecision(vector<bool> v) {
    decisionVector = v;
}

void Strategy::mutateDecision(int index) {
    decisionVector[index] = !decisionVector[index];
}

void Strategy::reportStrategy() {
    cout << "Utilities:\n";
    for (const auto &item : utilities) {
        cout << item << " ";
    }
    cout << "\nDecisin Vector:\n";
    for (const auto &range : decisionVector) {
        cout << range << " ";
    }
    cout << "Fitness: " << fitness << endl;
}