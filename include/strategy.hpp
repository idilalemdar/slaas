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
    void setDecision(vector<bool>);
    void addDecision(bool);
    void mutateDecision(int);
    void clearUtilities();
    vector<bool> getDecision() const;
    void reportStrategy(string, string);
};


#endif //SLAAS_STRATEGY_H
