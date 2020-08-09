#include "Renderer.hpp"

namespace FGE {

    void  Renderer::BeginScene() {}
    void Renderer::EndScene() {}

    void Renderer::Submit(const Ref<VertexArray> &vertexArray) {

        vertexArray->Bind();
        RenderCommand::DrawIndexed( vertexArray );

    }

} // namespace FGE
