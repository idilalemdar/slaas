#include "strategy.hpp"
#include <gtest/gtest.h>

TEST(StrategyTest1, Constructor) {
    vector<bool> v = {true, true, false, true, false, false, true, false, false, true, true, false};
    Strategy *st = new Strategy(v, 6, 6);
    st->setUtility(0,3);
    st->setUtility(1,2);
    st->setUtility(2,4);
    st->setUtility(3,3);
    st->setUtility(4,7);
    st->setUtility(5,5);
    EXPECT_EQ((4.0/6), st->getFitness());
    delete st;
}

TEST(StrategyTest2, Constructor) {
    vector<bool> v = {true, true, false, true, false, false, true, false, false, true, true, false};
    Strategy *st = new Strategy(v, 6, 6);
    st->setUtility(0,4);
    st->setUtility(1,5);
    st->setUtility(2,3);
    st->setUtility(3,9);
    st->setUtility(4,9);
    st->setUtility(5,6);
    EXPECT_EQ(1, st->getFitness());
    delete st;
}