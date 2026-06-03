#include <gtest/gtest.h>
#include "RGB.hpp"

TEST(RGBTest, StructuredBinding) {
    RGB c{10, 20, 30};
    auto [r, g, b] = c;
    EXPECT_EQ(r, 10);
    EXPECT_EQ(g, 20);
    EXPECT_EQ(b, 30);
}

TEST(RGBTest, GetFunctions) {
    RGB c{1, 2, 3};
    EXPECT_EQ(get<0>(c), 1);
    EXPECT_EQ(get<1>(c), 2);
    EXPECT_EQ(get<2>(c), 3);

    get<0>(c) = 7;
    get<1>(c) = 8;
    get<2>(c) = 9;
    EXPECT_EQ(c.r, 7);
    EXPECT_EQ(c.g, 8);
    EXPECT_EQ(c.b, 9);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
