#ifndef SLAAS_CORE_NETWORK_H
#define SLAAS_CORE_NETWORK_H

#include "common.hpp"
#include "strategy.hpp"
#include "allocation.hpp"

typedef struct SliceRequest {
    SliceType type;
    double cost;
    int lifetime;
    int utility;
} SliceRequest;

class CoreNW {
private:
    double availablePool = 1.0;
    Strategy& appliedStrategy;
    int evolutionTerm;
    vector<SliceRequest> activeSliceSet;
    vector<pair<ActiveSliceSet, SliceType>> freeDecision;
public:
    CoreNW(vector<pair<ActiveSliceSet, SliceType>> fd, Strategy& st, int term)
        : appliedStrategy(st), evolutionTerm(term), freeDecision(fd) {
        activeSliceSet.countTypeZero = 0;
        activeSliceSet.countTypeOne = 0;
        activeSliceSet.totalCost = 0;
        activeSliceSet.totalUtility = 0;
    }
    void operate(vector<SliceRequest>);
};


#endif //SLAAS_CORE_NETWORK_H
