#pragma once 

namespace FGE {

    enum class RendererAPI {

        None = 0,
        OpenGL = 1,

    };

    class Renderer {

    public:
        // virtual void Init() = 0;

        inline static RendererAPI GetAPI() { return s_RendererAPI; }
    
    private:
        static RendererAPI s_RendererAPI;

    };

}