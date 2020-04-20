#include "SGLog.h"
#include <spdlog/logger.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/msvc_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

static std::unique_ptr<spdlog::logger> g_logger;

int SG::SGLog::Initialize()
{
	auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	console_sink->set_level(spdlog::level::trace);  // message generating filter
	console_sink->set_pattern("[%t][%^%l%$]%v");

	auto msvc_sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
	msvc_sink->set_level(spdlog::level::trace);  // message generating filter
	msvc_sink->set_pattern("[%t][%^%l%$]%v");

	auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("GPCS4.log", true);
	file_sink->set_level(spdlog::level::trace);
	file_sink->set_pattern("[%t][%^%l%$]%v");

	g_logger.reset(new spdlog::logger("SGProject", { msvc_sink, file_sink, console_sink }));
	g_logger->set_level(spdlog::level::trace);  // message showing filter
	return 0;
}

void SG::SGLog::printf(LogLevel nLevel, const char* szFunction, const char* szSourcePath, int nLine, const char* szFormat, ...)
{
	if (!m_bEnabled)
	{
		return;
	}

	va_list stArgList;
	va_start(stArgList, szFormat);
	char szTempStr[LOG_STR_BUFFER_LEN + 1] = { 0 };
	vsprintf_s(szTempStr, LOG_STR_BUFFER_LEN, szFormat, stArgList);
	va_end(stArgList);

	switch (nLevel)
	{
	case LogLevel::Debug:
		g_logger->debug("{}({}): {}", szFunction, nLine, szTempStr);
		break;
	case LogLevel::Trace:
		g_logger->trace("{}({}): {}", szFunction, nLine, szTempStr);
		break;
	case LogLevel::Info:
		g_logger->info("{}({}): {}", szFunction, nLine, szTempStr);
		break;
	case LogLevel::Fixme:
		g_logger->warn("<FIXME>{}({}): {}", szFunction, nLine, szTempStr);
		break;
	case LogLevel::Warning:
		g_logger->warn("{}({}): {}", szFunction, nLine, szTempStr);
		break;
	case LogLevel::Error:
		g_logger->error("{}({}): {}", szFunction, nLine, szTempStr);
		break;
	case LogLevel::Graphic:
		g_logger->trace("<GRAPH>{}({}): {}", szFunction, nLine, szTempStr);
		break;
	}
}
