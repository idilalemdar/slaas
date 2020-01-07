#ifndef SLAAS_STRATEGY_H
#define SLAAS_STRATEGY_H

#include <vector>

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
};


#endif //SLAAS_STRATEGY_H
