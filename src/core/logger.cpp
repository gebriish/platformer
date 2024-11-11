#include "logger.h"

#include <iostream>
#include <iomanip>
#include <cstdarg>
#include <vector>
#include <string>

void Logger::log(LogLevel level, const char* message, ...)
{
	std::string prefix;
	std::string colorCode;

	switch (level)
	{
		case LogLevel::INFO:
			prefix = "[INFO] ";
			colorCode = "\033[32m";
			break;
		case LogLevel::WARNING:
			prefix = "[WARNING] ";
			colorCode = "\033[33m";
			break;
		case LogLevel::SEVERE:
			prefix = "[SEVERE] ";
			colorCode = "\033[31m";
			break;
	}

	va_list args;
	va_start(args, message);

	std::vector<char> buffer(1024);
	vsnprintf(buffer.data(), buffer.size(), message, args);
	
	va_end(args);

	std::cout << "\033[0m" << colorCode << prefix << buffer.data() << "\033[0m" << '\n';
}