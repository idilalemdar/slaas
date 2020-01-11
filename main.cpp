#include "core_network.hpp"
#include "allocation.hpp"
#include "genetic_algorithm.hpp"
#include "strategy.hpp"
#include "common.hpp"

#define EVOLUTION_TERM 6
#define POPULATION_SIZE 50
#define MAX_GEN 20
#define LAMBDA1 0.5
#define LAMBDA2 2
#define MU1 2
#define MU2 10

int requestID = 0;

map<int, vector<SliceRequest>> generateRequests(default_random_engine& generator, vector<double> costs, vector<int> utilities) {
    map<int, vector<SliceRequest>> results;

    poisson_distribution<int> dist_poisson_1(LAMBDA1);
    exponential_distribution<double> dist_exp_1(MU1);

    poisson_distribution<int> dist_poisson_2(LAMBDA2);
    exponential_distribution<double> dist_exp_2(MU2);

    for (int k = 0; k < EVOLUTION_TERM; ++k) {
        vector<SliceRequest> v;
        int numOfRequestsTypeOne = dist_poisson_1(generator);
        for (int j = 0; j < numOfRequestsTypeOne; ++j) {
            int lifetime1 = static_cast<int>(ceil(dist_exp_1(generator)));
            SliceRequest srq{requestID++, First, costs[0], lifetime1, utilities[0]};
            v.push_back(srq);
        }
        int numOfRequestsTypeTwo = dist_poisson_2(generator);
        for (int k = 0; k < numOfRequestsTypeTwo; ++k) {
            int lifetime2 = static_cast<int>(ceil(dist_exp_2(generator)));
            SliceRequest srq{requestID++, Second, costs[1], lifetime2, utilities[1]};
            v.push_back(srq);
        }
        results.insert(make_pair(k, v));
    }
    return  results;
}

int main(int argc, char **argv) {
    double c1 = stod(argv[2]);
    double c2 = stod(argv[3]);
    int u1 = stoi(argv[4]);
    int u2 = stoi(argv[5]);

    vector<double> costs{c1, c2};
    vector<int> utilities{u1, u2};

    string experiment = argv[1];

    AllocationSpace as(c1, c2, u1, u2);
    auto freeDecision = as.getFreeDecisionSpace();
    GeneticAlgorithm ga(EVOLUTION_TERM, as.getBestUtility(), POPULATION_SIZE, freeDecision.size());
    vector<Strategy>& population = ga.getCurrentPopulation();
    Strategy bestStrategy(population[0]);

    default_random_engine generator{static_cast<long unsigned int>(time(0))};
    string fname = "exp" + experiment + "_report.txt";
    for (int k = 0; k < MAX_GEN; ++k) {
        map<int, vector<SliceRequest>> requests(generateRequests(generator, costs, utilities));// generate requests for the next generation
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
        ga.evolve(); // evolve after the whole population goes through one evolution term
        ga.reportPopulation(fname, to_string(k));
        bestStrategy.reportStrategy(fname, to_string(k));
    }
    return 0;
}


