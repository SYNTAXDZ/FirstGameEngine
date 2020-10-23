
#pragma once

#include <Engine.hpp>

class PBRLayer : public FGE::Layer {

public:
    PBRLayer();
    virtual ~PBRLayer() = default;

    virtual void OnAttach() override;
    virtual void OnUpdate( FGE::Timestep ts ) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent( FGE::Event &event ) override;

private:
    FGE::Ref<FGE::VertexBuffer> m_VertexBuffer;
    FGE::Ref<FGE::IndexBuffer> m_IndexBuffer;
    FGE::Ref<FGE::VertexArray> m_VertexArray;
    FGE::CameraController m_CameraController;
    FGE::Ref<FGE::Shader> m_PBRShader;

    std::vector<glm::vec3> m_LightPositions;
    std::vector<glm::vec3> m_LightColors;

    FGE::Ref<FGE::Texture2D> m_AlbedoTexture;
    FGE::Ref<FGE::Texture2D> m_NormalTexture;
    FGE::Ref<FGE::Texture2D> m_MetallicTexture;
    FGE::Ref<FGE::Texture2D> m_RoughnessTexture;
    FGE::Ref<FGE::Texture2D> m_AOTexture;
    FGE::Ref<FGE::Sphere> m_Sphere;

};
