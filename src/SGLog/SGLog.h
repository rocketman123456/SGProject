#pragma once
#include "SGSingleton.h"

namespace SG
{
	enum class LogLevel : int
	{
		Trace = 0,
		Info,
		Debug,
		Fixme,
		Warning,
		Error,
		Graphic,
	};

	class SGLog : implements SGSingleton<SGLog>
	{
	public:
		int Initialize();
		void printf(LogLevel nLevel, const char* szFunction, const char* szSourcePath, int nLine, const char* szFormat, ...);
	protected:
		bool m_bEnabled = true;
	};
}

#define _LOG_PRINT_(level, format, ...)    ::SG::SGLog::GetSingleton().printf(level, __FUNCTION__, __FILE__, __LINE__, format, __VA_ARGS__)
// for debug print
#define LOG_DEBUG(format, ...) _LOG_PRINT_(::SG::LogLevel::Debug, format, __VA_ARGS__)
// for trace calling
#define LOG_TRACE(format, ...) _LOG_PRINT_(::SG::LogLevel::Trace, format, __VA_ARGS__)
// for info
#define LOG_INFO(format, ...) _LOG_PRINT_(::SG::LogLevel::Info, format, __VA_ARGS__)
// should be fixed, but without fix, the program should run, treat this as TODO
#define LOG_FIXME(format, ...) _LOG_PRINT_(::SG::LogLevel::Fixme, format, __VA_ARGS__)
// should be fixed, without this, program can run, but behaves unexpected
#define LOG_WARN(format, ...) _LOG_PRINT_(::SG::LogLevel::Warning, format, __VA_ARGS__)
// critical error, program can't go on
#define LOG_ERROR(format, ...) _LOG_PRINT_(::SG::LogLevel::Error, format, __VA_ARGS__)
// graphics info
#define LOG_GRAPHICS(format, ...) _LOG_PRINT_(::SG::LogLevel::Graphic, format, __VA_ARGS__)
