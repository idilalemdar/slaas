#ifndef SLAAS_GENETIC_ALGORITHM_H
#define SLAAS_GENETIC_ALGORITHM_H

#include "strategy.hpp"
#include "common.hpp"

class GeneticAlgorithm {
private:
    default_random_engine generator{static_cast<long unsigned int>(time(0))};
    double totalFitness = 0;
    int populationSize;
    int freeDecisionSpace;
    const double crossoverRate = 0.7;
    const double mutationRate = 0.2;
    vector<Strategy> population;
    void reproduce();
    void crossover();
    void mutate();
    void xover(int);
    void initializePopulation();
    void calculateTotalFitness();
    void calculateProportions(vector<double>&);
    void createNewPopulation(const vector<double>&, vector<Strategy>&);
public:
    void reportPopulation();
    GeneticAlgorithm(int, int);
    vector<Strategy>& getCurrentPopulation();
    void evolve();
};


#endif //SLAAS_GENETIC_ALGORITHM_H
