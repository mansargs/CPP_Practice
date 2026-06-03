#pragma once

#include <map>
#include <string>
#include <filesystem>
#include <vector>
#include <algorithm>

std::map<std::string, std::vector<std::filesystem::path>> directory_scanner(const std::string& path);
