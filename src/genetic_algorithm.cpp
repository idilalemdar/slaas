#include "genetic_algorithm.hpp"

GeneticAlgorithm::GeneticAlgorithm(int term, int max, int size, int fd) {
    evolutionTerm = term;
    maxPossibleUtility = max;
    populationSize = size;
    freeDecisionSpace = fd;
    initializePopulation();
}

void GeneticAlgorithm::initializePopulation() {
    for (int i = 0; i < populationSize; ++i) {
        for (int j = 0; j < freeDecisionSpace; ++j) {
            // TODO: implement
        }
        population.push_back(true);
    }
}

vector<Strategy>& GeneticAlgorithm::getCurrentPopulation() const {
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