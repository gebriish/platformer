#pragma once

enum class LogLevel
{
	INFO,
	WARNING,
	SEVERE
};

class Logger
{
public:
	static void log(LogLevel level, const char* message, ...);
};