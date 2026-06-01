#pragma once

#include <memory>
#include <string>

class Logger {
	private:
		class Impl;
		std::unique_ptr<Impl> impl;
	public:
		Logger();
		~Logger();
		Logger(const Logger& other);
		Logger& operator=(const Logger& other);
		Logger(Logger&&) noexcept;
		Logger& operator=(Logger&&) noexcept;
		void log(const std::string& msg);
		void set_level(int level);
};
