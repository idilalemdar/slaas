#ifndef SLAAS_ALLOCATION_H
#define SLAAS_ALLOCATION_H

#include <utility>
#include <vector>

using namespace std;

enum SliceType {
    First,
    Second
};

typedef struct ActiveSliceSet {
    int countTypeZero;
    int countTypeOne;
    double totalCost;
    int totalUtility;
} ActiveSliceSet;

class AllocationSpace {
private:
    const double resourcePool = 1.0;
    pair<double, double> costs;
    pair<int, int> utilities;
    vector<pair<ActiveSliceSet, SliceType>> freeDecision;
    vector<ActiveSliceSet> calculateResourceFeasibility();
    void calculateFreeDecision();
    void reportResourceFeasibility(const ActiveSliceSet&, int);
    void reportFreeDecision(const pair<ActiveSliceSet, SliceType>&, int);
    void addElementToFreeDecision( ActiveSliceSet, SliceType, int);
public:
    AllocationSpace(double, double, int, int);
    vector<pair<ActiveSliceSet, SliceType>> getFreeDecisionSpace() const;
};

#endif //SLAAS_ALLOCATION_H
