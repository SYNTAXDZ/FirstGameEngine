#include "Renderer.hpp"

namespace FGE {

    Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

    void Renderer::BeginScene( Camera &camera ) {

        s_SceneData->ProjectionMatrix = camera.GetProjectionMatrix();
        s_SceneData->ViewMatrix = camera.GetViewMatrix();

    }
    void Renderer::EndScene() {}

    void Renderer::Submit( const Ref<VertexArray> &vertexArray, const Ref<Shader> &shader, const glm::mat4& transform ) {

      shader->Bind();
      shader->SetMat4( "u_Projection", s_SceneData->ProjectionMatrix );
      shader->SetMat4( "u_View", s_SceneData->ViewMatrix );
      shader->SetMat4( "u_Model", transform );

      vertexArray->Bind();
      RenderCommand::DrawIndexed(vertexArray);

    }

} // namespace FGE
