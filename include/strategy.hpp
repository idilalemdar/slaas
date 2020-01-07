#ifndef SLAAS_STRATEGY_H
#define SLAAS_STRATEGY_H

#include "common.hpp"

using namespace std;

class Strategy {
private:
    int evolutionTerm;
    int maxPossibleUtility;
    vector<int> utilities;
    double fitness;
    vector<bool> decisionVector;
public:
    Strategy(int, int);
    void calculateFitness();
    double getFitness() const;
    void addUtility(int);
    void addDecision(bool);
    void clearUtilities();
    vector<bool> getDecision() const;
};


#endif //SLAAS_STRATEGY_H
