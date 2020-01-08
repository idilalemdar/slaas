#include "strategy.hpp"
#include <gtest/gtest.h>

StrategyBase *instance = StrategyBase::getInstance();
instance->setValues(6,6);

TEST(StrategyTest1, Constructor) {
    vector<bool> v = {true, true, false, true, false, false, true, false, false, true, true, false};
    Strategy st;
    for (auto const& ele : v) {
        st.addDecision(ele);
    }
    st.addUtility(3);
    st.addUtility(2);
    st.addUtility(4);
    st.addUtility(3);
    st.addUtility(7);
    st.addUtility(5);
    st.calculateFitness();
    EXPECT_EQ((4.0/6), st.getFitness());
}

TEST(StrategyTest2, Constructor) {
    vector<bool> v = {true, true, false, true, false, false, true, false, false, true, true, false};
    Strategy st;
    for (auto const& ele : v) {
        st.addDecision(ele);
    }
    st.addUtility(4);
    st.addUtility(5);
    st.addUtility(3);
    st.addUtility(9);
    st.addUtility(9);
    st.addUtility(6);
    st.calculateFitness();
    EXPECT_EQ(1, st.getFitness());
}