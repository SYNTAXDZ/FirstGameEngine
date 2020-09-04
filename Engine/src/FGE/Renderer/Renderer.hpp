#pragma once 

#include "Shader.hpp"
#include "RenderCommand.hpp"
#include "Camera.hpp"

namespace FGE {

    class Renderer {

    public:
        static void BeginScene( Camera& camera );
        static void EndScene();

        static void Submit( const Ref<VertexArray> &vertexArray, const Ref<Shader> &shader, const glm::mat4 &transform );

        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

    private:
        struct SceneData {

            glm::mat4 ProjectionMatrix;
            glm::mat4 ViewMatrix;

        };

        static Scope<SceneData> s_SceneData;

    };


}
