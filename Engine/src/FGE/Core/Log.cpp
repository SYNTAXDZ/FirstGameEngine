#include "Log.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace FGE {

    Ref<spdlog::logger> Log::s_CoreLogger;
	Ref<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {
        // this pattern stand's for a color and Time[%T] and the name of the Logger%n, finally
        // The Log Message %v%$
		spdlog::set_pattern("%^[%T] %n: %v%$");
        // Set The Name of The CoreLogger To FirstGameEngine
		s_CoreLogger = spdlog::stdout_color_mt( "FirstGameEngine" );
        // And Set The Level Of Severty in The Console
		s_CoreLogger->set_level( spdlog::level::trace );

		s_ClientLogger = spdlog::stdout_color_mt( "APP" );
		s_ClientLogger->set_level( spdlog::level::trace );
	
    }

}