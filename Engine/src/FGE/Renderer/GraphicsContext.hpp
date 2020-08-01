#pragma once

#include "FGE/Core/Base.hpp"

struct GLFWwindow;

namespace FGE {

    class GraphicsContext {
    
    public:
        virtual ~GraphicsContext() = default;

        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;

        static Ref<GraphicsContext> Create( GLFWwindow* windowHandle );

    };

} // namespace FGE
