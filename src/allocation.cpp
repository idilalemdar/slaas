#include "allocation.hpp"

AllocationSpace::AllocationSpace(double c1, double c2, int u1, int u2) {
    costs.first = c1;
    costs.second = c2;
    utilities.first = u1;
    utilities.second = u2;
    calculateFreeDecision();
}

vector<pair< ActiveSliceSet, SliceType>> AllocationSpace::getFreeDecisionSpace() const {
    return freeDecision;
}

void AllocationSpace::reportResourceFeasibility(const ActiveSliceSet& ele, int index) {
    ofstream report("allocation.txt", ofstream::app);
    report << index << ":\n# of type 0 slice: " << ele.countTypeZero << "\n# of type 1 slice: "
        << ele.countTypeOne << "\nTotal cost: " << ele.totalCost << "\nTotal utility: "
        << ele.totalUtility << "\n\n";
    report.close();
}

vector< ActiveSliceSet> AllocationSpace::calculateResourceFeasibility() {
    int maxTypeOne = static_cast<int>(floor(resourcePool / costs.first));
    vector< ActiveSliceSet> result;
    int j = 0;
    int index = 0;
    double typeOneCost = 0;
    double totalCost = 0;
    int totalUtility;
    ofstream report("allocation.txt", ofstream::app);
    report << "Space of resource feasibility:\n\n";
    report.close();
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
            reportResourceFeasibility(c, index++);
        }
        typeOneCost += costs.first;
        totalCost = typeOneCost;
        j = 0;
    }
    return result;
}

void AllocationSpace::reportFreeDecision(const pair< ActiveSliceSet, SliceType>& p, int index) {
    ofstream report("allocation.txt", ofstream::app);
    ActiveSliceSet c = p.first;
    report << index << ":\n# of type 0 slice: " << c.countTypeZero << "\n# of type 1 slice: "
           << c.countTypeOne << "\nTotal cost: " << c.totalCost << "\nTotal utility: "
           << c.totalUtility << "\nAdded slice type: " << p.second << "\n\n";
    report.close();
}

void AllocationSpace::addElementToFreeDecision( ActiveSliceSet ele, SliceType type, int index) {
    pair< ActiveSliceSet, SliceType> p(ele, type);
    freeDecision.push_back(p);
    reportFreeDecision(p, index);
}

void AllocationSpace::calculateFreeDecision() {
    vector< ActiveSliceSet> resourceFeasibility = calculateResourceFeasibility();
    double costBefore;
    int index = 0;
    ofstream report("allocation.txt", ofstream::app);
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

int AllocationSpace::getBestUtility() const {
    return bestUtility;
}