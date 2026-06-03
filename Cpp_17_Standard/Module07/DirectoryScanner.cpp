#include "DirectoryScanner.hpp"

std::map<std::string, std::vector<std::filesystem::path>> directory_scanner(const std::string& path) {
	namespace fs = std::filesystem;
	std::map<std::string, std::vector<fs::path>> table;
	std::error_code ec;
	fs::path dir(path);

	auto st = fs::status(dir, ec);
	if (!ec && fs::is_directory(st)) {
		auto options = fs::directory_options::skip_permission_denied;
		fs::recursive_directory_iterator it(dir, options, ec);
		if (ec)
			return table;
		fs::recursive_directory_iterator end;
		for (; it != end; it.increment(ec)) {
			if (ec) {
				ec.clear();
				continue;
			}
			const fs::directory_entry& entry = *it;
			if (!entry.is_regular_file(ec)) {
				if (ec)
					ec.clear();
				continue;
			}
			const auto& p = entry.path();
			auto ext = p.extension().string();
			std::transform(ext.begin(), ext.end(), ext.begin(),[](unsigned char c) { return std::tolower(c); });
			table[ext].push_back(p);
		}
	}
	return table;
}
