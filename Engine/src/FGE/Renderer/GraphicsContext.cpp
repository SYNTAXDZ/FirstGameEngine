#include "GraphicsContext.hpp"
#include "Platform/OpenGL/GLGraphicsContext.hpp"


namespace FGE {

    Ref<GraphicsContext> GraphicsContext::Create( GLFWwindow* windowHandle ) {

        return CreateRef<GLGraphicsContext>( windowHandle );

    }

} // namespace FGE
