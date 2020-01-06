#include "allocation.hpp"
#include <gtest/gtest.h>

TEST(AllocationTest1, Constructor) {
    AllocationSpace as(0.3, 0.3, 2, 1);
    EXPECT_EQ(12, as.getFreeDecisionSpace().size());
    EXPECT_EQ(6, as.getBestUtility());
}

TEST(AllocationTest2, Constructor) {
    AllocationSpace as(0.3, 0.2, 2, 1);
    EXPECT_EQ(18, as.getFreeDecisionSpace().size());
    EXPECT_EQ(6, as.getBestUtility());
}