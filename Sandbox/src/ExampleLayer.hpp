#pragma once

#include <Engine.hpp>

class ExampleLayer : public FGE::Layer {

public:
    ExampleLayer();
    virtual ~ExampleLayer() = default;

    virtual void OnAttach() override;
    virtual void OnUpdate( FGE::Timestep ts ) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent( FGE::Event &event ) override;

private:
    FGE::Ref<FGE::VertexBuffer> m_VertexBuffer;
    FGE::Ref<FGE::IndexBuffer> m_IndexBuffer;
    FGE::Ref<FGE::VertexArray> m_VertexArray;
    FGE::CameraController m_CameraController;
    FGE::Ref<FGE::Shader> m_Shader;
    FGE::Ref<FGE::Texture2D> m_Texture2D;

};
