#pragma once
#include "PlutoniumGameEngine/Core/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_sinks.h"

namespace PGE {


	class Log
	{
	public:
		static void Init();
		inline static PGE::Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; };
		inline static PGE::Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; };

	private:

		static PGE::Ref<spdlog::logger> s_CoreLogger;
		static PGE::Ref<spdlog::logger> s_ClientLogger;
	
	};
}

// Core log macros
#define PGE_CORE_TRACE(...)     PGE::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PGE_CORE_INFO(...)     PGE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PGE_CORE_WARN(...)     PGE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PGE_CORE_ERROR(...)    PGE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PGE_CORE_FATAL(...)    PGE::Log::GetCoreLogger()->fatal(__VA_ARGS__)


// Client log macros
#define PGE_CLIENT_TRACE(...)	      PGE::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PGE_CLIENT_INFO(...)	      PGE::Log::GetClientLogger()->info(__VA_ARGS__)
#define PGE_CLIENT_WARN(...)	      PGE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define PGE_CLIENT_ERROR(...)	      PGE::Log::GetClientLogger()->error(__VA_ARGS__)
#define PGE_CLIENT_FATAL(...)	      PGE::Log::GetClientLogger()->fatal(__VA_ARGS__) 