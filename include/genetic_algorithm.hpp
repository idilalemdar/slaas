#ifndef SLAAS_GENETIC_ALGORITHM_H
#define SLAAS_GENETIC_ALGORITHM_H

#include "strategy.hpp"
#include "common.hpp"

class GeneticAlgorithm {
private:
    int evolutionTerm;
    int maxPossibleUtility;
    int populationSize;
    int freeDecisionSpace;
    const double crossoverRate = 0.7;
    const double mutationRate = 0.3;
    vector<Strategy> population;
    void reproduce();
    void crossover();
    void mutate();
    void initializePopulation();
public:
    GeneticAlgorithm(int, int, int, int);
    vector<Strategy>& getCurrentPopulation();
    void evolve();
};


#endif //SLAAS_GENETIC_ALGORITHM_H
