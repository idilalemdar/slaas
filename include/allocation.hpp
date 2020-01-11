#ifndef SLAAS_ALLOCATION_H
#define SLAAS_ALLOCATION_H

#include <utility>
#include "common.hpp"

enum SliceType {
    First,
    Second
};

typedef struct ActiveSliceSet {
    int countTypeZero;
    int countTypeOne;
    double totalCost;
    int totalUtility;
    bool operator==(ActiveSliceSet const& rhs) const {
        return (this->countTypeZero == rhs.countTypeZero)
            && (this->countTypeOne == rhs.countTypeOne)
            && (this->totalUtility == rhs.totalUtility)
            && (this->totalCost == rhs.totalCost);
    }
} ActiveSliceSet;

class AllocationSpace {
private:
    int bestUtility = 0;
    const double resourcePool = 1.0;
    pair<double, double> costs;
    pair<int, int> utilities;
    vector<pair<ActiveSliceSet, SliceType>> freeDecision;
    vector<ActiveSliceSet> calculateResourceFeasibility();
    void calculateFreeDecision();
    void addElementToFreeDecision(ActiveSliceSet, SliceType);
public:
    AllocationSpace(double, double, int, int);
    vector<pair<ActiveSliceSet, SliceType>> getFreeDecisionSpace() const;
    int getBestUtility() const;
};

#endif //SLAAS_ALLOCATION_H
