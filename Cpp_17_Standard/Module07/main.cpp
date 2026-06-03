#include "DirectoryScanner.hpp"
#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

static void create_file(const fs::path& p) {
	fs::create_directories(p.parent_path());
	std::ofstream(p.string()).put('x');
}

TEST(DirectoryScanner, GroupsByExtension) {
	fs::path dir = fs::temp_directory_path() / "scanner_test";
	fs::remove_all(dir);
	create_file(dir / "a.cpp");
	create_file(dir / "b.cpp");
	create_file(dir / "c.txt");
	auto result = directory_scanner(dir.string());
	EXPECT_EQ(result[".cpp"].size(), 2);
	EXPECT_EQ(result[".txt"].size(), 1);
	fs::remove_all(dir);
}

TEST(DirectoryScanner, EmptyDirectory) {
	fs::path dir = fs::temp_directory_path() / "scanner_empty";
	fs::remove_all(dir);
	fs::create_directories(dir);
	auto result = directory_scanner(dir.string());
	EXPECT_TRUE(result.empty());
	fs::remove_all(dir);
}

TEST(DirectoryScanner, NoExtensionFiles) {
	fs::path dir = fs::temp_directory_path() / "scanner_no_ext";
	fs::remove_all(dir);
	create_file(dir / "Makefile");
	create_file(dir / "README");
	auto result = directory_scanner(dir.string());
	EXPECT_EQ(result[""].size(), 2);
	fs::remove_all(dir);
}

TEST(DirectoryScanner, RecursiveScan) {
	fs::path dir = fs::temp_directory_path() / "scanner_recursive";
	fs::remove_all(dir);
	create_file(dir / "a.cpp");
	create_file(dir / "sub" / "b.cpp");
	create_file(dir / "sub" / "c.txt");
	auto result = directory_scanner(dir.string());
	EXPECT_EQ(result[".cpp"].size(), 2);
	EXPECT_EQ(result[".txt"].size(), 1);
	fs::remove_all(dir);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
