#ifndef SLAAS_GENETIC_ALGORITHM_H
#define SLAAS_GENETIC_ALGORITHM_H

#include "strategy.hpp"
#include "common.hpp"

class GeneticAlgorithm {
private:
    default_random_engine generator{static_cast<long unsigned int>(time(0))};
    double totalFitness = 0;
    int evolutionTerm;
    int maxPossibleUtility;
    int populationSize;
    int freeDecisionSpace;
    const double crossoverRate = 0.7;
    const double mutationRate = 0.3;
    vector<Strategy> population;
    void crossover();
    void mutate();
    void initializePopulation();
    void calculateTotalFitness();
    void calculateProportions(vector<double>&);
    void createNewPopulation(const vector<double>&, vector<Strategy>&);
public:
    void reportPopulation();
    GeneticAlgorithm(int, int, int, int);
    vector<Strategy>& getCurrentPopulation();
    void evolve();
    void reproduce();
};


#endif //SLAAS_GENETIC_ALGORITHM_H
