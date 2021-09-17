#include <log.hpp>
#include <string.h>

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

	void Log::debug(const char* msg)
	{
		if (debugCallback != NULL)
		{
			char debugMessage[255] = { 0 };
			memcpy(debugMessage, "DEBUG:", 6);
			strcat(debugMessage, msg);
			debugCallback(debugMessage);
		}
	}

	void Log::info(const char* msg)
	{
		if (infoCallback != NULL)
		{
			char infoMessage[255] = { 0 };
			memcpy(infoMessage, "INFO:", 5);
			strcat(infoMessage, msg);
			infoCallback(infoMessage);
		}
	}

	void Log::error(const char* msg)
	{
		if (errorCallback != NULL)
		{
			char errorMessage[255] = { 0 };
			memcpy(errorMessage, "ERROR:", 6);
			strcat(errorMessage, msg);
			errorCallback(errorMessage);
		}
	}
}