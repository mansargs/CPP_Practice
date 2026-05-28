#include <memory>
#include <cstdio>
#include <iostream>

auto deleter_lambda = [](FILE* f) {
	if (f) {
		fclose(f);
		std::cout << "Deleter has called\n";
	}
};

std::unique_ptr<FILE, decltype(deleter_lambda)> make_resource(const char* filename, const char* mode) {
	FILE* f = fopen(filename, mode);
	if (!f)
		throw std::runtime_error("Failed to open file");
	return std::unique_ptr<FILE, decltype(deleter_lambda)>(f, deleter_lambda);
}

int main() {
	try {
		auto file = make_resource("test.txt", "w+");
		const char* text = "Hello RAII FILE!\n";
		std::fputs(text, file.get());
		std::rewind(file.get());
		char buffer[100];
		if (std::fgets(buffer, sizeof(buffer), file.get())) {
			std::cout << "Read from file: " << buffer;
		}
		std::cout << "File will now be automatically closed...\n";

	} catch (const std::exception& e) {
		std::cout << "Error: " << e.what() << "\n";
	}
	std::cout << "End of main\n";
	return 0;
}
