#include <gtest/gtest.h>
#include "AST.hpp"

static Expr make_literal(int value) {
    return Expr{Literal{value}};
}

static Expr make_add(Expr left, Expr right) {
    return Expr{Add{std::make_unique<Expr>(std::move(left)), std::make_unique<Expr>(std::move(right))}};
}

static Expr make_mul(Expr left, Expr right) {
    return Expr{Mul{std::make_unique<Expr>(std::move(left)), std::make_unique<Expr>(std::move(right))}};
}

static Expr make_neg(Expr expr) {
    return Expr{Neg{std::make_unique<Expr>(std::move(expr))}};
}

TEST(EvalTest, Literal) {
    EXPECT_EQ(eval(make_literal(5)), 5);
}

TEST(EvalTest, AddAndMul) {
    Expr expr = make_add(make_literal(2), make_mul(make_literal(3), make_literal(4)));
    EXPECT_EQ(eval(expr), 14);
}

TEST(EvalTest, NestedNegation) {
    Expr expr = make_neg(make_add(make_literal(1), make_neg(make_literal(2))));
    EXPECT_EQ(eval(expr), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
