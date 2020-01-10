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
    int lifetime;
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
    void reportResourceFeasibility(const ActiveSliceSet&, int);
    void reportFreeDecision(const pair<ActiveSliceSet, SliceType>&, int);
    void addElementToFreeDecision(ActiveSliceSet, SliceType, int);
public:
    AllocationSpace(double, double, int, int);
    vector<pair<ActiveSliceSet, SliceType>> getFreeDecisionSpace() const;
    int getBestUtility() const;
};

#endif //SLAAS_ALLOCATION_H
