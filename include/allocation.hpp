#ifndef SLAAS_ALLOCATION_H
#define SLAAS_ALLOCATION_H

#include <utility>
#include<vector>

using namespace std;

enum SliceType {
    First,
    Second
};

typedef struct Case {
    int countTypeZero;
    int countTypeOne;
    double totalCost;
    int totalUtility;
}Case;

class AllocationSpace {
private:
    const double resourcePool = 1.0;
    pair<double, double> costs;
    pair<int, int> utilities;
    vector<pair<Case, SliceType>> freeDecision;
    vector<Case> calculateResourceFeasibility();
    void calculateFreeDecision();
public:
    AllocationSpace(double, double, int, int);
    vector<pair<Case, SliceType>> getFreeDecisionSpace() const;
};

#endif //SLAAS_ALLOCATION_H
