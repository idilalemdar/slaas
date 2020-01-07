#include "genetic_algorithm.hpp"
#include <random>
#include <iostream>

GeneticAlgorithm::GeneticAlgorithm(int term, int max, int size, int fd) {
    evolutionTerm = term;
    maxPossibleUtility = max;
    populationSize = size;
    freeDecisionSpace = fd;
    initializePopulation();
}

void GeneticAlgorithm::initializePopulation() {
    default_random_engine generator;
    uniform_real_distribution<double> distribution(0.0,1.0);
    for (int i = 0; i < populationSize; ++i) {
        Strategy st(evolutionTerm, maxPossibleUtility);
        for (int j = 0; j < freeDecisionSpace; ++j) {
            double roll = distribution(generator);
            cout << roll << endl;
            if (roll <= 0.6) { // generate true with probability 0.6
                st.addDecision(true);
            } else {
                st.addDecision(false);
            }
        }
        population.push_back(st);
    }
}

vector<Strategy>& GeneticAlgorithm::getCurrentPopulation() {
    return population;
}

void GeneticAlgorithm::evolve() {
    reproduce();
    crossover();
    mutate();
}

void GeneticAlgorithm::reproduce() {

}

void GeneticAlgorithm::crossover() {

}

void GeneticAlgorithm::mutate() {

}