#pragma once 

#include "Shader.hpp"
#include "RenderCommand.hpp"

namespace FGE {

    class Renderer {

    public:
        static void BeginScene();
        static void EndScene();

        static void Submit( const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader );
        // static void Submit( const Ref<VertexArray> &vertexArray );

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

    };

}
