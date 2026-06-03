#include <gtest/gtest.h>
#include "Monadic.hpp"

TEST(OptionalMap, TransformsValue)
{
	std::optional<int> opt = 5;

	auto res = optional_map(opt, [](int x) {
		return x * 2;
	});

	ASSERT_TRUE(res.has_value());
	EXPECT_EQ(*res, 10);
}

TEST(OptionalMap, PropagatesNullopt)
{
	std::optional<int> opt;

	auto res = optional_map(opt, [](int x) {
		return x * 2;
	});

	EXPECT_FALSE(res.has_value());
}

// optional_and_then tests
TEST(OptionalAndThen, ChainsSuccessfully)
{
	std::optional<int> opt = 2;

	auto res = optional_and_then(opt, [](int x) {
		return std::optional<int>(x + 1);
	});

	ASSERT_TRUE(res.has_value());
	EXPECT_EQ(*res, 3);
}

TEST(OptionalAndThen, PropagatesNullopt)
{
	std::optional<int> opt;

	auto res = optional_and_then(opt, [](int x) {
		return std::optional<int>(x + 1);
	});

	EXPECT_FALSE(res.has_value());
}

// -----------------------------
// PIPELINE TESTS
// -----------------------------

TEST(Pipeline, Success)
{
	auto res1 = optional_and_then(parse_int("2"), validate_range);
	auto res2 = optional_and_then(res1, lookup);
	auto final_res = optional_map(res2, format);

	ASSERT_TRUE(final_res.has_value());
	EXPECT_EQ(*final_res, "Result: two");
}

TEST(Pipeline, ParseFailure)
{
	auto res1 = optional_and_then(parse_int("abc"), validate_range);
	auto res2 = optional_and_then(res1, lookup);
	auto final_res = optional_map(res2, format);

	EXPECT_FALSE(final_res.has_value());
}

TEST(Pipeline, ValidationFailure)
{
	auto res1 = optional_and_then(parse_int("100"), validate_range);
	auto res2 = optional_and_then(res1, lookup);
	auto final_res = optional_map(res2, format);

	EXPECT_FALSE(final_res.has_value());
}

TEST(Pipeline, LookupFailure)
{
	auto res1 = optional_and_then(parse_int("999"), validate_range);
	auto res2 = optional_and_then(res1, lookup);
	auto final_res = optional_map(res2, format);

	EXPECT_FALSE(final_res.has_value());
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
