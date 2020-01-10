#include "core_network.hpp"
#include "allocation.hpp"
#include "genetic_algorithm.hpp"
#include "strategy.hpp"
#include "common.hpp"

#define EVOLUTION_TERM 6
#define POPULATION_SIZE 10
#define MAX_GEN 20
#define LAMBDA = 0.5;
#define MU = 2;

vector<ActiveSliceSet> generateRequests(auto& generator) {

}

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
        vector<ActiveSliceSet> requests;// generate requests for the next generation
        for (int j = 0; j < POPULATION_SIZE; ++j) {
            CoreNW cnw(freeDecision, population[j], EVOLUTION_TERM);
            for (int i = 0; i < EVOLUTION_TERM; ++i) {
                cnw.operate(requests[i]);

                // cnw.operate() should:
                // handle requests, release them when their lifetime is over
                // calculate the utility generated
                // add that utility to the strategy
            }
            population[j].calculateFitness();
            population[j].clearUtilities();
            if (bestStrategy.getFitness() < population[j].getFitness()) {
                bestStrategy = population[j];
            }
        }
        ga.evolve(); // evolve after each evolution term
    }
    return 0;
}


