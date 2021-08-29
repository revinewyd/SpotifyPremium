#pragma once
#include "stdafx.h"

class Logger {
private:
	auto current_datetime ()
	{
		static struct tm newtime;
		static __time64_t long_time;
		_time64 (&long_time);
		localtime_s (&newtime, &long_time);
		return std::put_time (&newtime, "%d-%b-%Y %H:%M:%S");
	}

	std::ofstream log_stream;
	const bool read (std::string_view app, std::string_view key, int def_value = 0) {
		if (1 == GetPrivateProfileInt (app.data (), key.data (), def_value, "./config.ini")) {
			return true;
		}
		return false;
	}


public:
	Logger () {
		if (read ("Config", "Log")) {
			log_stream.open ("blockthespot_log.txt", std::ios::out | std::ios::app);
			//m_log << "BlockTheSpot - Build date: " << __TIMESTAMP__ << std::endl;
		}
	}

	~Logger () {
		if (log_stream.is_open()) {
			log_stream.flush ();
			log_stream.close ();
		}
	}

	void Log (std::string_view log) {
		if (log_stream.is_open ()) {
			std::stringstream message;
			message << "LOG | " << current_datetime () << " - " << log;
			log_stream << message.str() << std::endl;
		}
			
	}


};
