#ifndef SLAAS_STRATEGY_H
#define SLAAS_STRATEGY_H

#include "common.hpp"

using namespace std;

class StrategyBase {
private:
    static StrategyBase* instance;
    StrategyBase();
protected:
    static int evolutionTerm;
    static int maxPossibleUtility;
public:
    void setValues(int, int);
    static StrategyBase* getInstance();
    ~StrategyBase();
};

class Strategy: public StrategyBase {
private:
    vector<int> utilities;
    double fitness = 0;
    vector<bool> decisionVector;
public:
    Strategy();
    void calculateFitness();
    double getFitness() const;
    void addUtility(int);
    void setDecision(vector<bool>);
    void addDecision(bool);
    void clearUtilities();
    vector<bool> getDecision() const;
};


#endif //SLAAS_STRATEGY_H
