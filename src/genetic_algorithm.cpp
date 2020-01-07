#include "genetic_algorithm.hpp"
#include <iostream>
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
        report << "Strategy " << i << ": ";
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
    reportPopulation();
}

vector<Strategy>& GeneticAlgorithm::getCurrentPopulation() {
    return population;
}

void GeneticAlgorithm::evolve() {
    reproduce();
    crossover();
    mutate();
}

void GeneticAlgorithm::calculateTotalFitness() {  // OK
    totalFitness = 0;
    for (auto const &ele : population) {
        totalFitness += ele.getFitness();
    }
}

void GeneticAlgorithm::reportPopulation() {
    ofstream report("populationInfo.txt", ofstream::app);
    for (auto const& ele: population) {
        report << "Fitness:" << ele.getFitness() << " Decision vector: ";
        for (auto const& decision: ele.getDecision()) {
            report << decision << " ";
        }
        report << endl;
    }
    report << endl;
    report.close();
}

void GeneticAlgorithm::calculateProportions(vector<double>& proportions) {
    for (auto const &ele : population) {
        double proportion = ele.getFitness() / totalFitness;
        if (proportions.empty()) {  // cumulative roulette wheel
            proportions.push_back(proportion);
        } else {
            proportions.push_back(proportion + proportions.back());
        }
    }
}

void GeneticAlgorithm::createNewPopulation(const vector<double>& proportions, vector<Strategy>& new_population) {
    default_random_engine generator{static_cast<long unsigned int>(time(0))};
    uniform_real_distribution<double> distribution(0.0, 1.0);
    for (int i = 0; i < populationSize; ++i) {
        double roll = distribution(generator); // this nigga is not random. why not random??
        int index = 0;
        cout << roll << " ";
        while (roll > proportions[index]) {
            index++;
        }
        cout << endl;
        new_population.push_back(population[index]);
    }
}

void GeneticAlgorithm::reproduce() {  // fitness proportionate selection
    ofstream report("populationInfo.txt", ofstream::app);
    calculateTotalFitness();
    report << "Total fitness in the population: " << totalFitness << endl;

    vector<double> proportions;
    calculateProportions(proportions);

    vector<Strategy> new_population;
    createNewPopulation(proportions, new_population);

    population = new_population;
    report << "Before shuffle:\n";
    report.close();
    reportPopulation();
    default_random_engine generator{static_cast<long unsigned int>(time(0))};
    shuffle(population.begin(), population.end(), generator);
    ofstream rep("populationInfo.txt", ofstream::app);
    rep << "After shuffle:\n";
    rep.close();
    reportPopulation();
}

void GeneticAlgorithm::crossover() {

}

void GeneticAlgorithm::mutate() {

}