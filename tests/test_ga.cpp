#include <gtest/gtest.h>
#include "genetic_algorithm.hpp"

default_random_engine generator{static_cast<long unsigned int>(time(0))};
uniform_int_distribution<int> distribution(0,6);

TEST(GA2, Evolve) {
    GeneticAlgorithm ga(6, 6, 10, 12);
    vector<Strategy>& pop = ga.getCurrentPopulation();
    for(auto& st: pop) {
        for (int i = 0; i < 6; ++i) {
            int roll = distribution(generator);
            st.addUtility(roll);
        }
        st.calculateFitness();
    }
    ga.evolve();
}

TEST(GA3, EvolveTwice) {
    GeneticAlgorithm ga(6, 6, 10, 12);
    vector<Strategy>& pop = ga.getCurrentPopulation();
    for(int j = 0; j < 2; ++j) {
        for(auto& st: pop) {
            st.clearUtilities();
            for (int i = 0; i < 6; ++i) {
                int roll = distribution(generator);
                st.addUtility(roll);
            }
            st.calculateFitness();
        }
        ga.evolve();
    }
}