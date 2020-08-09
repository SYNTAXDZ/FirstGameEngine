#pragma once

#include "FGE/Renderer/RendererAPI.hpp"

namespace FGE {

    class GLRendererAPI : public RendererAPI {

    public:
        virtual ~GLRendererAPI() = default;
        virtual void Init() override;
        virtual void Clear() override;
        virtual void SetClearColor( const glm::vec4 &color ) override;

        virtual void DrawIndexed( const Ref<VertexArray> &vertexArray ) override;

    };

}
