// Copyright 2022 GHA Test Team

#include <gtest/gtest.h>
#include "Automata.h"

#define TRANSITION_TEST(from, op, to) { \
    Automata automata = Automata(from); \
    automata.op; \
    EXPECT_EQ(automata.position(), to); \
    }

TEST(automata, off_good) {
    TRANSITION_TEST(down, on(), waiting);
}

TEST(automata, off_bad) {
    TRANSITION_TEST(down, off(), invalid);
    TRANSITION_TEST(down, coin(10), invalid);
    TRANSITION_TEST(down, choice(0), invalid);
    TRANSITION_TEST(down, check(), invalid);
    TRANSITION_TEST(down, cancel(), invalid);
    TRANSITION_TEST(down, cook(), invalid);
    TRANSITION_TEST(down, finish(), invalid);
}

TEST(automata, wait_good) {
    TRANSITION_TEST(waiting, coin(100), accepting);
    TRANSITION_TEST(waiting, off(), down);
}

TEST(automata, wait_bad) {
    TRANSITION_TEST(waiting, on(), invalid);
    TRANSITION_TEST(waiting, choice(0), invalid);
    TRANSITION_TEST(waiting, check(), invalid);
    TRANSITION_TEST(waiting, cancel(), invalid);
    TRANSITION_TEST(waiting, cook(), invalid);
    TRANSITION_TEST(waiting, finish(), invalid);
}

TEST(automata, accept_good) {
    TRANSITION_TEST(accepting, cancel(), waiting);
    TRANSITION_TEST(accepting, coin(100), accepting);
    TRANSITION_TEST(accepting, choice(0), checking);
}

TEST(automata, accept_bad) {
    TRANSITION_TEST(accepting, off(), invalid);
    TRANSITION_TEST(accepting, on(), invalid);
    TRANSITION_TEST(accepting, check(), invalid);
    TRANSITION_TEST(accepting, cook(), invalid);
    TRANSITION_TEST(accepting, finish(), invalid);
}

TEST(automata, normal) {
    Automata automata;
    automata.on();
    EXPECT_EQ(automata.position(), States::waiting);
    automata.coin(50);
    automata.coin(100);
    EXPECT_EQ(automata.position(), States::accepting);
    automata.choice(0);
    EXPECT_EQ(automata.position(), States::checking);
    automata.cook();
    EXPECT_EQ(automata.position(), States::cooking);
    EXPECT_TRUE(automata.finish() != nullptr);
    automata.off();
    EXPECT_TRUE(automata.end());
}

TEST(automata, not_enough_money) {
    Automata automata;
    automata.on();
    EXPECT_EQ(automata.position(), States::waiting);
    automata.coin(150);
    EXPECT_EQ(automata.position(), States::accepting);
    automata.choice(1);
    automata.cook();
    EXPECT_EQ(automata.position(), States::invalid);
}

TEST(automata, invalid_drink) {
    Automata automata;
    automata.on();
    EXPECT_EQ(automata.position(), States::waiting);
    automata.coin(150);
    EXPECT_EQ(automata.position(), States::accepting);
    automata.choice(10);
    automata.cook();
    EXPECT_EQ(automata.position(), States::invalid);
}

TEST(automata, good_states) {
    Automata automata;
    automata = Automata(States::accepting);
    EXPECT_FALSE(automata.end());
    automata = Automata(States::checking);
    EXPECT_FALSE(automata.end());
    automata = Automata(States::cooking);
    EXPECT_FALSE(automata.end());
    automata = Automata(States::down);
    EXPECT_TRUE(automata.end());
    automata = Automata(States::invalid);
    EXPECT_FALSE(automata.end());
    automata = Automata(States::waiting);
    EXPECT_FALSE(automata.end());
}