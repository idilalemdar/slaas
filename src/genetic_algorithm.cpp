#include "genetic_algorithm.hpp"

GeneticAlgorithm::GeneticAlgorithm(int term, int max, int size, int fd) {
    evolutionTerm = term;
    maxPossibleUtility = max;
    populationSize = size;
    freeDecisionSpace = fd;
    initializePopulation();
}

void GeneticAlgorithm::initializePopulation() {
    default_random_engine generator{static_cast<long unsigned int>(time(0))};
    uniform_real_distribution<double> distribution(0.0,1.0);
    ofstream report("initialGeneration.txt", ofstream::app);
    report << "Initializing generation zero:\n\n";
    for (int i = 0; i < populationSize; ++i) {
        report << "Strategy " << i << ":\n";
        Strategy st(evolutionTerm, maxPossibleUtility);
        for (int j = 0; j < freeDecisionSpace; ++j) {
            double roll = distribution(generator);
            if (roll <= 0.6) { // generate true with probability 0.6
                st.addDecision(true);
                report << "T ";
            } else {
                st.addDecision(false);
                report << "F ";
            }
        }
        report << endl;
        population.push_back(st);
    }
    report << endl;
    report.close();
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