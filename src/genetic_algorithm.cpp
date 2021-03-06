#include "genetic_algorithm.hpp"

GeneticAlgorithm::GeneticAlgorithm(int term, int max, int size, int fd) {
    evolutionTerm = term;
    maxPossibleUtility = max;
    populationSize = size;
    freeDecisionSpace = fd;
    initializePopulation();
}

void GeneticAlgorithm::initializePopulation() {
    uniform_real_distribution<double> distribution(0.0,1.0);
    for (int i = 0; i < populationSize; ++i) {
        Strategy st(evolutionTerm, maxPossibleUtility);
        for (int j = 0; j < freeDecisionSpace; ++j) {
            double roll = distribution(generator);
            if (roll <= 0.7) { // generate true with probability 0.7
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

void GeneticAlgorithm::calculateTotalFitness() {  // OK
    totalFitness = 0;
    for (auto const &ele : population) {
        totalFitness += ele.getFitness();
    }
}

void GeneticAlgorithm::reportPopulation(string fname, string i) {
    ofstream report(fname, ofstream::app);
    report << "Total fitness in the population at generation " + i + ": " << totalFitness << endl << endl;
    for (auto const& ele: population) {
        report << " Decision vector: ";
        for (auto const& decision: ele.getDecision()) {
            report << decision << " ";
        }
        report << endl;
    }
    report << endl;
    report.close();
}

void GeneticAlgorithm::calculateProportions(vector<double>& proportions) {
    double cumulativeProportion = 0;
    for (auto const &ele : population) {
        cumulativeProportion += ele.getFitness() / totalFitness;
        proportions.push_back(cumulativeProportion);
    }
}

void GeneticAlgorithm::createNewPopulation(const vector<double>& proportions, vector<Strategy>& new_population) {
    uniform_real_distribution<double> distribution(0.0, 1.0);
    for (int i = 0; i < populationSize; ++i) {
        double roll = distribution(generator);
        int index = 0;
        while (roll > proportions[index]) {
            index++;
        }
        new_population.push_back(population[index]);
    }
}

void GeneticAlgorithm::reproduce() {  // fitness proportionate selection
    ofstream report;
    calculateTotalFitness();

    vector<double> proportions;
    calculateProportions(proportions);

    vector<Strategy> new_population;
    createNewPopulation(proportions, new_population);

    population = new_population;
    calculateTotalFitness();

    shuffle(population.begin(), population.end(), generator);
}

void GeneticAlgorithm::xover(int index) {
    uniform_int_distribution<int> distribution(1, freeDecisionSpace - 1);
    int roll = distribution(generator); // crossover point

    vector<bool> dv1(population[index].getDecision());
    vector<bool> dv2(population[index + 1].getDecision());

    auto dv1start = dv1.begin();
    auto dv1end = dv1.end();
    auto dv2start = dv2.begin();
    auto dv2end = dv2.end();

    auto split1 = dv1start + roll;
    auto split2 = dv2start + roll;

    vector<bool> dv1_tail(split1, dv1end);
    vector<bool> dv2_tail(split2, dv2end);
    vector<bool> dv1_head(dv1start, split1);
    vector<bool> dv2_head(dv2start, split2);

    dv1_head.insert(dv1_head.end(), dv2_tail.begin(), dv2_tail.end());
    dv2_head.insert(dv2_head.end(), dv1_tail.begin(), dv1_tail.end());

    population[index].setDecision(dv1_head);
    population[index + 1].setDecision(dv2_head);
}

void GeneticAlgorithm::crossover() {
    uniform_real_distribution<double> distribution(0.0, 1.0);
    for (int i = 0; i < populationSize; i += 2) {
        double roll = distribution(generator);
        if (roll <= crossoverRate) { // crossover happens
            xover(i);
        }
    }
}

void GeneticAlgorithm::mutateBits(int index) {
    Strategy& individual = population[index];
    uniform_real_distribution<double> distribution(0.0, 1.0);
    for (int i = 0; i < freeDecisionSpace; ++i) {
        double roll = distribution(generator);
        if (roll <= mutationRate) {
            individual.mutateDecision(i);
        }
    }
}

void GeneticAlgorithm::mutate() {
    for (int j = 0; j < populationSize; ++j) {
        for (int i = 0; i < mutationRound; ++i) {
            mutateBits(j);
        }
    }
}