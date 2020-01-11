#include "allocation.hpp"

AllocationSpace::AllocationSpace(double c1, double c2, int u1, int u2) {
    costs.first = c1;
    costs.second = c2;
    utilities.first = u1;
    utilities.second = u2;
    calculateFreeDecision();
}

vector<pair<ActiveSliceSet, SliceType>> AllocationSpace::getFreeDecisionSpace() const {
    return freeDecision;
}

vector<ActiveSliceSet> AllocationSpace::calculateResourceFeasibility() {
    int maxTypeOne = static_cast<int>(floor(resourcePool / costs.first));
    vector< ActiveSliceSet> result;
    int j = 0;
    double typeOneCost = 0;
    double totalCost = 0;
    int totalUtility;
    for (int i = 0; i <= maxTypeOne; ++i) {
        while (totalCost <= resourcePool) {
            totalUtility = i * utilities.first + j * utilities.second;
            if (totalUtility > bestUtility) {
                bestUtility = totalUtility;
            }
            const ActiveSliceSet& c = {i, j, totalCost, totalUtility};
            result.push_back(c);
            totalCost += costs.second;
            j++;
        }
        typeOneCost += costs.first;
        totalCost = typeOneCost;
        j = 0;
    }
    return result;
}

void AllocationSpace::addElementToFreeDecision(ActiveSliceSet ele, SliceType type) {
    pair<ActiveSliceSet, SliceType> p(ele, type);
    freeDecision.push_back(p);
}

void AllocationSpace::calculateFreeDecision() {
    vector<ActiveSliceSet> resourceFeasibility(calculateResourceFeasibility());
    double costBefore;
    for (auto const &ele : resourceFeasibility) {
        costBefore = ele.totalCost;
        if (costBefore + costs.first <= resourcePool) {
            addElementToFreeDecision(ele, First);
        }
        if (costBefore + costs.second <= resourcePool) {
            addElementToFreeDecision(ele, Second);
        }
    }
}

int AllocationSpace::getBestUtility() const {
    return bestUtility;
}