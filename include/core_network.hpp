#ifndef SLAAS_CORE_NETWORK_H
#define SLAAS_CORE_NETWORK_H

#include "common.hpp"
#include "strategy.hpp"
#include "allocation.hpp"

typedef struct SliceRequest {
    int id;
    SliceType type;
    double cost;
    int lifetime;
    int utility;
    bool operator==(SliceRequest const& rhs) const {
        return this->id == rhs.id;
    }
} SliceRequest;

class CoreNW {
private:
    double availablePool = 1.0;
    Strategy& appliedStrategy;
    int evolutionTerm;
    ActiveSliceSet status;
    vector<SliceRequest> activeSliceSet;
    vector<pair<ActiveSliceSet, SliceType>> freeDecision;
    void removeSlices();
    bool allocate(const SliceRequest&);
public:
    CoreNW(vector<pair<ActiveSliceSet, SliceType>> fd, Strategy& st, int term)
        : appliedStrategy(st), evolutionTerm(term), freeDecision(fd) {
        status.countTypeZero = 0;
        status.countTypeOne = 0;
        status.totalCost = 0;
        status.totalUtility = 0;
    }
    void operate(vector<SliceRequest>);
};


#endif //SLAAS_CORE_NETWORK_H
