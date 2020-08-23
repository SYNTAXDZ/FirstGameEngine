#include "Renderer.hpp"

namespace FGE {

    void Renderer::BeginScene() {}
    void Renderer::EndScene() {}

    void Renderer::Submit( const Ref<VertexArray> &vertexArray, const Ref<Shader>& shader ) {

        vertexArray->Bind();
        shader->Bind();
        RenderCommand::DrawIndexed( vertexArray );

    }

} // namespace FGE
