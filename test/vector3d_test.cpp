#include "gtest/gtest.h"

TEST(Footest, fails_demo) {
    EXPECT_EQ(true, false);
}

TEST(Footest, success_demo) {
    EXPECT_EQ(true, true);
}