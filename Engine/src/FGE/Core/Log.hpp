#pragma once

#include "Base.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace FGE {

    class Log {

    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;

    };

}

// Core log macros
#define FGE_CORE_TRACE(...)    ::FGE::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FGE_CORE_INFO(...)     ::FGE::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FGE_CORE_WARN(...)     ::FGE::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FGE_CORE_ERROR(...)    ::FGE::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FGE_CORE_CRITICAL(...) ::FGE::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define FGE_TRACE(...)         ::FGE::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FGE_INFO(...)          ::FGE::Log::GetClientLogger()->info(__VA_ARGS__)
#define FGE_WARN(...)          ::FGE::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FGE_ERROR(...)         ::FGE::Log::GetClientLogger()->error(__VA_ARGS__)
#define FGE_CRITICAL(...)      ::FGE::Log::GetClientLogger()->critical(__VA_ARGS__)