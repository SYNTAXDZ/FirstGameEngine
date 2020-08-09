#include "RenderCommand.hpp"

#include "Platform/OpenGL/GLRendererAPI.hpp"

namespace FGE {

    Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();

}
