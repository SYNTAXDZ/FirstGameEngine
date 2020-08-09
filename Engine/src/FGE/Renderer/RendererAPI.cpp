#include "RendererAPI.hpp"

#include "Platform/OpenGL/GLRendererAPI.hpp"

namespace FGE {

    RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

    Scope<RendererAPI> RendererAPI::Create() {

        switch( s_API ) {

            case RendererAPI::API::None:
                FGE_CORE_ASSERT( false, "RendererAPI::None is currently not supported!" );
                return nullptr;

            case RendererAPI::API::OpenGL:
                return CreateScope<GLRendererAPI>();

        }

        FGE_CORE_ASSERT( false, "Unknown RendererAPI!" );
        return nullptr;

    }

}
