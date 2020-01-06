#include "allocation.hpp"
#include <cmath>
#include <fstream>

AllocationSpace::AllocationSpace(double c1, double c2, int u1, int u2) {
    costs.first = c1;
    costs.second = c2;
    utilities.first = u1;
    utilities.second = u2;
    calculateFreeDecision();
}

vector<pair<Case, SliceType>> AllocationSpace::getFreeDecisionSpace() const {
    return freeDecision;
}

void AllocationSpace::reportResourceFeasibility(const Case& ele, int index) {
    ofstream report("report.txt", ofstream::app);
    report << index << ":\n# of type 0 slice: " << ele.countTypeZero << "\n# of type 1 slice: "
        << ele.countTypeOne << "\nTotal cost: " << ele.totalCost << "\nTotal utility: "
        << ele.totalUtility << "\n\n";
    report.close();
}

vector<Case> AllocationSpace::calculateResourceFeasibility() {
    int maxTypeOne = static_cast<int>(floor(resourcePool / costs.first));
    vector<Case> result;
    int j = 0;
    int index = 0;
    double typeOneCost = 0;
    double totalCost = 0;
    ofstream report("report.txt", ofstream::app);
    report << "Space of resource feasibility:\n\n";
    report.close();
    for (int i = 0; i <= maxTypeOne; ++i) {
        while (totalCost <= resourcePool) {
            const Case& c = {i, j, totalCost, i * utilities.first + j * utilities.second};
            result.push_back(c);
            totalCost += costs.second;
            j++;
            reportResourceFeasibility(c, index++);
        }
        typeOneCost += costs.first;
        totalCost = typeOneCost;
        j = 0;
    }
    return result;
}

void AllocationSpace::reportFreeDecision(const pair<Case, SliceType>& p, int index) {
    ofstream report("report.txt", ofstream::app);
    Case c = p.first;
    report << index << ":\n# of type 0 slice: " << c.countTypeZero << "\n# of type 1 slice: "
           << c.countTypeOne << "\nTotal cost: " << c.totalCost << "\nTotal utility: "
           << c.totalUtility << "\nAdded slice type: " << p.second << "\n\n";
    report.close();
}

void AllocationSpace::addElementToFreeDecision(Case ele, SliceType type, int index) {
    pair<Case, SliceType> p(ele, type);
    freeDecision.push_back(p);
    reportFreeDecision(p, index);
}

void AllocationSpace::calculateFreeDecision() {
    vector<Case> resourceFeasibility = calculateResourceFeasibility();
    double costBefore;
    int index = 0;
    ofstream report("report.txt", ofstream::app);
    report << "Space of free decision:\n\n";
    report.close();
    for (auto const &ele : resourceFeasibility) {
        costBefore = ele.totalCost;
        if (costBefore + costs.first <= resourcePool) {
            addElementToFreeDecision(ele, First, index++);
        }
        if (costBefore + costs.second <= resourcePool) {
            addElementToFreeDecision(ele, Second, index++);
        }
    }
}