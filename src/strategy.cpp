#include "strategy.hpp"

StrategyBase* StrategyBase::instance = 0;

StrategyBase::~StrategyBase() {
    delete instance;
}

static StrategyBase* StrategyBase::getInstance() {
    if(instance == nullptr) {
        instance = new StrategyBase();
    }
    return instance;
}

void StrategyBase::setValues(int term, int max) {
    evolutionTerm = term;
    maxPossibleUtility = max;
}

Strategy::Strategy() {
    StrategyBase *instance = StrategyBase::getInstance();
}

vector<bool> Strategy::getDecision() const {
    return decisionVector;
}

double Strategy::getFitness() const {
    return fitness;
}

void Strategy::calculateFitness() { // OK
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

void Strategy::setDecision(vector<bool> v) {
    decisionVector = v;
}