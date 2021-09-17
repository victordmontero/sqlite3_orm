#ifndef LOG_HPP_
#define LOG_HPP_

namespace sqlite3_orm
{
	typedef void (*DEBUG_CALLBACK)(const char*);

	class Log
	{
		static DEBUG_CALLBACK debugCallback;
		static DEBUG_CALLBACK infoCallback;
		static DEBUG_CALLBACK errorCallback;

	public:
		Log() {};
		~Log() {};

		static void setLogDebugCallback(DEBUG_CALLBACK);
		static void setLogInfoCallback(DEBUG_CALLBACK);
		static void setLogErrorCallback(DEBUG_CALLBACK);
		static void debug(const char* msg);
		static void info(const char* msg);
		static void error(const char* msg);
	};
}

#endif