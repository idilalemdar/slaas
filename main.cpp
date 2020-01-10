#include "core_network.hpp"
#include "allocation.hpp"
#include "genetic_algorithm.hpp"
#include "strategy.hpp"
#include "common.hpp"

#define EVOLUTION_TERM 6
#define POPULATION_SIZE 10
#define MAX_GEN 20
#define LAMBDA 0.5
#define MU 2

int requestID = 0;

map<int, vector<SliceRequest>> generateRequests(default_random_engine& generator, vector<double> costs, vector<int> utilities) {
    map<int, vector<SliceRequest>> results;
    poisson_distribution<int> dist_poisson(LAMBDA);
    exponential_distribution<double> dist_exp(MU);

    for (int k = 0; k < EVOLUTION_TERM; ++k) {
        vector<SliceRequest> v;
        for (int i = 0; i < 2; ++i) {
            int numOfRequests = dist_poisson(generator);
            for (int j = 0; j < numOfRequests; ++j) {
                int lifetime = static_cast<int>(ceil(dist_exp(generator)));
                SliceRequest srq{requestID++, static_cast<SliceType>(i), costs[i], lifetime, utilities[i]};
                v.push_back(srq);
            }
        }
        results.insert(make_pair(k, v));
    }
    return  results;
}

int main(int argc, char **argv) {
    double c1, c2;
    int u1, u2;
    cin >> c1 >> c2 >> u1 >> u2;
    vector<double> costs{c1, c2};
    vector<int> utilities{u1, u2};

    AllocationSpace as(c1, c2, u1, u2);
    auto freeDecision = as.getFreeDecisionSpace();
    GeneticAlgorithm ga(EVOLUTION_TERM, as.getBestUtility(), POPULATION_SIZE, freeDecision.size());
    vector<Strategy>& population = ga.getCurrentPopulation();
    Strategy bestStrategy(population[0]);

    default_random_engine generator{static_cast<long unsigned int>(time(0))};

    for (int k = 0; k < MAX_GEN; ++k) {
        map<int, vector<SliceRequest>> requests = generateRequests(generator, costs, utilities);// generate requests for the next generation
        for (int j = 0; j < POPULATION_SIZE; ++j) {
            Strategy& st = population[j];
            CoreNW cnw(freeDecision, st, EVOLUTION_TERM);
            for (int i = 0; i < EVOLUTION_TERM; ++i) {
                cnw.operate(requests[i]);
            }
            st.calculateFitness();
            if (bestStrategy.getFitness() < st.getFitness()) {
                bestStrategy = st;
            }
            st.clearUtilities();
        }
        ga.evolve(); // evolve after each evolution term
    }
    return 0;
}


