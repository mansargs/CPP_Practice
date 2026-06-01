#include "Logger.hpp"
#include <iostream>

struct Logger::Impl {
		int level = 0;

		void log(const std::string& msg) {
			if (level > 0) {
				std::cout << "[LOG]: " << msg << "\n";
			} else {
				std::cout << "[SKIPPED]\n";
			}
		}
};

Logger::Logger() : impl(std::make_unique<Impl>()) {}

Logger::~Logger() = default;

Logger::Logger(const Logger& other) : impl(std::make_unique<Impl>(*other.impl)) {}

Logger& Logger::operator=(const Logger& other) {
	if (this != &other) {
		impl = std::make_unique<Impl>(*other.impl);
	}
	return *this;
}

Logger::Logger(Logger&&) noexcept = default;

Logger& Logger::operator=(Logger&&) noexcept = default;

void Logger::log(const std::string& msg) {
	impl->log(msg);
}

void Logger::set_level(int level) {
	impl->level = level;
}
