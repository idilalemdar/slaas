#ifndef SLAAS_STRATEGY_H
#define SLAAS_STRATEGY_H

#include <vector>

using namespace std;

class Strategy {
private:
    int maxPossibleUtility;
    int evolutionTerm;
    int *utilities;
    double fitness;
    vector<bool> decisionVector;
    void calculateFitness();
public:
    Strategy(const vector<bool>&, int, int);
    ~Strategy();
    double getFitness();
    void setUtility(int, int);
};


#endif //SLAAS_STRATEGY_H
