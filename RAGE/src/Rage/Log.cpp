#include "rgpch.h"
#include "Log.h"

namespace Rage
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%H:%M:%S %z]  %=5n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("RAGE");
		s_CoreLogger->set_level(spdlog::level::trace);
		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}
