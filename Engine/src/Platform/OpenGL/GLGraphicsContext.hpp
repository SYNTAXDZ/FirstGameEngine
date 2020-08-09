#pragma once

#include "FGE/Renderer/GraphicsContext.hpp"

struct GLFWwindow;

namespace FGE {

    class GLGraphicsContext : public GraphicsContext {

    public:
        GLGraphicsContext( GLFWwindow* windowHandle );

        virtual void Init() override;
        virtual void SwapBuffers() override;
    
    private:
        GLFWwindow* m_WindowHandle;

    };
    
} // namespace FGE
