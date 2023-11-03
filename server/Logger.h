#pragma once

#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
#include <memory>

class Logger
{
public:
	static Logger* get_instance();
	void log(const std::string& msg);
	~Logger();

private:
	Logger();

	static std::unique_ptr<Logger> m_instance;
	std::ofstream m_log_file;
};


#endif // LOGGER_H