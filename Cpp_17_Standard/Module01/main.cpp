#include "Serialize.hpp"

#include <string>
#include <iostream>
#include <sstream>
#include <gtest/gtest.h>

struct MyType {
	int a;

	std::string to_string() const {
		return "MyType{" + std::to_string(a) + "}";
	}
};

struct BadType {
	int x;
};

class CoutCapture {
	public:
		std::stringstream buffer;
		std::streambuf* old;

		CoutCapture() {
			old = std::cout.rdbuf(buffer.rdbuf());
		}

		~CoutCapture() {
			std::cout.rdbuf(old);
		}

		std::string get() const {
			return buffer.str();
		}
};

TEST(Serialize, Integral) {
	CoutCapture cap;
	serialize(42);

	EXPECT_NE(cap.get().find("42"), std::string::npos);
}

TEST(Serialize, Floating) {
	CoutCapture cap;
	serialize(3.14159);

	// float formatting is not stable in iostream
	EXPECT_NE(cap.get().find("3.14159"), std::string::npos);
}

TEST(Serialize, String) {
	CoutCapture cap;
	serialize(std::string("hello world"));

	EXPECT_NE(cap.get().find("hello world"), std::string::npos);
}

TEST(Serialize, CString) {
	CoutCapture cap;
	serialize("hello c-string");

	EXPECT_NE(cap.get().find("hello c-string"), std::string::npos);
}

TEST(Serialize, CustomTypeWithToString) {
	CoutCapture cap;
	MyType m{123};
	serialize(m);

	EXPECT_NE(cap.get().find("MyType{123}"), std::string::npos);
}

TEST(Serialize, CustomTypeWithoutToString) {
	CoutCapture cap;
	BadType b{5};
	serialize(b);
	EXPECT_FALSE(cap.get().empty());
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
