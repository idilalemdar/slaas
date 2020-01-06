#include "allocation.hpp"
#include <cmath>
#include <iostream>

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
    cout << index << ":\n# of type 0 slice: " << ele.countTypeZero << "\n# of type 1 slice: "
        << ele.countTypeOne << "\nTotal cost: " << ele.totalCost << "\nTotal utility: "
        << ele.totalUtility << "\n\n";
}

vector<Case> AllocationSpace::calculateResourceFeasibility() {
    int maxTypeOne = static_cast<int>(floor(resourcePool / costs.first));
    vector<Case> result;
    int j = 0;
    int k = 0;
    double typeOneCost = 0;
    double totalCost = 0;
    for (int i = 0; i <= maxTypeOne; ++i) {
        while (totalCost <= resourcePool) {
            const Case& c = {i, j, totalCost, i * utilities.first + j * utilities.second};
            result.push_back(c);
            totalCost += costs.second;
            j++;
            k++;
            reportResourceFeasibility(c, k);
        }
        typeOneCost += costs.first;
        totalCost = typeOneCost;
        j = 0;
    }
    return result;
}

void AllocationSpace::calculateFreeDecision() {
    vector<Case> resourceFeasibility = calculateResourceFeasibility();
    double costBefore;
    for (auto const ele : resourceFeasibility) {
        costBefore = ele.totalCost;
        if (costBefore + costs.first <= resourcePool) {
            freeDecision.push_back(make_pair(ele, First));
        }
        if (costBefore + costs.second <= resourcePool) {
            freeDecision.push_back(make_pair(ele, Second));
        }
    }
}