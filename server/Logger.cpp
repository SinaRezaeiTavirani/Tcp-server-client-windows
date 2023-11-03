#include "Logger.h"
#include <iostream>


std::unique_ptr<Logger> Logger::m_instance = nullptr;

Logger::Logger()
{
	m_log_file.open("log.txt", std::ios_base::app);

	if (!m_log_file)
	{
		std::cerr << "FAILD TO OPEN LOG FILE" << std::endl;
		exit(1);
	}
}

Logger* Logger::get_instance()
{
	if (!m_instance)
	{
		m_instance.reset(new Logger);
	}
	return m_instance.get();
}

void Logger::log(const std::string& msg)
{
	Logger::m_log_file << msg << std::endl;
}

Logger::~Logger()
{
	if (m_log_file.is_open())
	{
		m_log_file.close();
	}
}
