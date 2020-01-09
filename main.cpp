#include "core_network.hpp"
#include "allocation.hpp"
#include "genetic_algorithm.hpp"
#include "strategy.hpp"
#include "common.hpp"

#define EVOLUTION_TERM 6
#define POPULATION_SIZE 10
#define MAX_GEN 20

int main(int argc, char **argv) {
    double c1, c2;
    int u1, u2;
    cin >> c1 >> c2 >> u1 >> u2;

    AllocationSpace as(c1, c2, u1, u2);
    auto freeDecision = as.getFreeDecisionSpace();
    GeneticAlgorithm ga(EVOLUTION_TERM, as.getBestUtility(), POPULATION_SIZE, freeDecision.size());
    vector<Strategy>& population = ga.getCurrentPopulation();
    Strategy& bestStrategy = population[0];
    for (int k = 0; k < MAX_GEN; ++k) {
        for (int j = 0; j < POPULATION_SIZE; ++j) {
            CoreNW cnw(freeDecision, population[j], EVOLUTION_TERM);
            cnw.operate();
            if (bestStrategy.getFitness() < population[j].getFitness()) {
                bestStrategy = population[j];
            }

            // cnw.operate() should (for evolutionTerm times):
            // clear utilities of the strategy
            // generate requests, allocate (or not allocate)
            // space for them, release them when their lifetime is over
            // calculate the utility generated after each operations period
            // add that utility to the strategies
            // calculate fitness after 1 evolution term
        }
        ga.evolve(); // evolve after each evolution term
    }
    return 0;
}


