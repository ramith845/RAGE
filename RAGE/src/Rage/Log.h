#pragma once

#include "Core.h"
// This ignores all warnings raised inside External headers
#pragma warning(push, 1)
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#pragma warning(pop)

namespace Rage
{
	class RAGE_API Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<RAGE_API spdlog::logger> s_CoreLogger;
		static std::shared_ptr<RAGE_API spdlog::logger> s_ClientLogger;
	};

}

#define RG_CORE_INFO(...)   ::Rage::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RG_CORE_WARN(...)   ::Rage::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RG_CORE_ERROR(...)	::Rage::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RG_CORE_TRACE(...)	::Rage::Log::GetCoreLogger()->trace(__VA_ARGS__)

#define RG_CLIENT_INFO(...)   ::Rage::Log::GetClientLogger()->info(__VA_ARGS__)
#define RG_CLIENT_WARN(...)   ::Rage::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RG_CLIENT_ERROR(...)  ::Rage::Log::GetClientLogger()->error(__VA_ARGS__)
#define RG_CLIENT_TRACE(...)  ::Rage::Log::GetClientLogger()->trace(__VA_ARGS__)