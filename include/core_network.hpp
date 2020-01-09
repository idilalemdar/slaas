#ifndef SLAAS_CORE_NETWORK_H
#define SLAAS_CORE_NETWORK_H

#include "common.hpp"
#include "strategy.hpp"
#include "allocation.hpp"

class CoreNW {
private:
    double availablePool = 1.0;
    const double lambda = 0.5;
    const int mu = 2;
    Strategy appliedStrategy;
    int evolutionTerm;
    ActiveSliceSet activeSliceSet;
    vector<pair<ActiveSliceSet, SliceType>> freeDecision;
public:
    CoreNW(vector<pair<ActiveSliceSet, SliceType>> fd, Strategy& st, int term)
        : appliedStrategy(st), evolutionTerm(term), freeDecision(fd) {}
    void operate();
};


#endif //SLAAS_CORE_NETWORK_H
