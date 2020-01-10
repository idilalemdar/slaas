#include "core_network.hpp"

void CoreNW::removeSlices() {
    for (auto& ele : activeSliceSet) {
        ele.lifetime -= 1;
        if (ele.lifetime == 0) {
            status.totalCost -= ele.cost;
            status.totalUtility -= ele.utility;
            if (ele.type == First) {
                status.countTypeZero -= 1;
            } else {
                status.countTypeOne -= 1;
            }
            availablePool += ele.cost;
            activeSliceSet.erase(remove(activeSliceSet.begin(), activeSliceSet.end(), ele), activeSliceSet.end());
        }
    }
}

bool CoreNW::allocate(const SliceRequest& request) {
    pair<ActiveSliceSet, SliceType> element = make_pair(status, request.type);
    vector<pair<ActiveSliceSet, SliceType>>::iterator iter = find(freeDecision.begin(), freeDecision.end(), element);
    if (iter != freeDecision.end()) { // if the request is in the space of free decision
        vector<bool> st(appliedStrategy.getDecision());
        return st[iter - freeDecision.begin()];
    }
    return false;
}

void CoreNW::operate(vector<SliceRequest> requests) {
    removeSlices();
    if (!requests.empty()) {
        for (const auto &item : requests) {
            if (allocate(item)) {
                availablePool -= item.cost;
                activeSliceSet.push_back(item);
                status.totalCost += item.cost;
                status.totalUtility += item.utility;
                if (item.type == First) {
                    status.countTypeZero += 1;
                } else {
                    status.countTypeOne += 1;
                }
                appliedStrategy.addUtility(status.totalUtility);
            }
        }
    }
}