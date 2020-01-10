#include "core_network.hpp"

void CoreNW::operate(vector<SliceRequest> requests) {
    // iterate through the activeSLiceSet, reduce their lifetimes by 1
    // pop those whose lifetime become 0, give back their resources
    // check if idle resources are sufficient for the new requests
    // if they are, check the strategy
    // if T, reduce idle resources accordingly
    // push the request to the active slice set
    // calculate utility in the operations period
    // push that utility to the strategy
}