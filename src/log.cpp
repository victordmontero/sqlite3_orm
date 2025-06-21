#include <cstdio>
#include <log.hpp>
#include <string.h>

#include <cstdarg>

namespace sqlite3_orm
{
	DEBUG_CALLBACK Log::debugCallback = NULL;
	DEBUG_CALLBACK Log::infoCallback = NULL;
	DEBUG_CALLBACK Log::errorCallback = NULL;

	void Log::setLogDebugCallback(DEBUG_CALLBACK callback)
	{
		debugCallback = callback;
	}

	void Log::setLogInfoCallback(DEBUG_CALLBACK callback)
	{
		infoCallback = callback;
	}

	void Log::setLogErrorCallback(DEBUG_CALLBACK callback)
	{
		errorCallback = callback;
	}

	void Log::debug(const char* msg, ...)
	{
		if (debugCallback != NULL)
		{
			char debugMessage[255] = { 0 };
      va_list varlist;
      va_start(varlist, msg);
      const size_t PREFIX_LENGTH = 6;
			memcpy(debugMessage, "DEBUG:", PREFIX_LENGTH);
      vsnprintf(debugMessage + PREFIX_LENGTH, sizeof(debugMessage) - PREFIX_LENGTH, msg, varlist);
			debugCallback(debugMessage);
      va_end(varlist);
		}
	}

	void Log::info(const char* msg, ...)
	{
		if (infoCallback != NULL)
		{
			char infoMessage[255] = { 0 };
      va_list varlist;
      va_start(varlist, msg);
      const size_t PREFIX_LENGTH = 5;
			memcpy(infoMessage, "INFO:", 5);
      vsnprintf(infoMessage + PREFIX_LENGTH, sizeof(infoMessage) - PREFIX_LENGTH, msg, varlist);
			infoCallback(infoMessage);
      va_end(varlist);
		}
	}

	void Log::error(const char* msg, ...)
	{
		if (errorCallback != NULL)
		{
			char errorMessage[255] = { 0 };
      va_list varlist;
      va_start(varlist, msg);
      const size_t PREFIX_LENGTH = 6;
			memcpy(errorMessage, "ERROR:", 6);
      vsnprintf(errorMessage + PREFIX_LENGTH, sizeof(errorMessage) - PREFIX_LENGTH, msg, varlist);
			errorCallback(errorMessage);
      va_end(varlist);
		}
	}
}
