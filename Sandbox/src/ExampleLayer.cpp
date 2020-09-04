#include "ExampleLayer.hpp"

#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

ExampleLayer::ExampleLayer() : Layer( "ExampleLayer" ), m_CameraController( 800.0f / 600.0f ) {

  m_VertexArray = FGE::VertexArray::Create();

  m_Shader = FGE::Shader::Create(
      "/home/syntax/Base/Knowledge/learn_cpp/CppProjects/FirstGameEngine/"
      "Sandbox/assets/shaders/Texture.glsl");

  m_Texture2D = FGE::Texture2D::Create(
      "/home/syntax/Base/Knowledge/learn_cpp/CppProjects/FirstGameEngine/"
      "Sandbox/assets/textures/ChernoLogo.png");

}

void ExampleLayer::OnAttach() {

  float vertices[5 * 3] = {
      -0.5f, -0.5f, 0.0f, -1.0f, -1.0f,
      0.5f, -0.5f, 0.0f,  1.0f,  -1.0f,
      0.0f, 0.5f,  0.0f,  0.5f, 1.0f,
  };

  float squareVertices[5 * 4] = {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f, -0.5f,
                                 0.0f,  1.0f,  0.0f, 0.5f, 0.5f, 0.0f, 1.0f,
                                 1.0f,  -0.5f, 0.5f, 0.0f, 0.0f, 1.0f};

  uint32_t indices[] = {0, 1, 2};
  uint32_t squareIndices[] = {0, 1, 2, 2, 3, 0 };

  m_VertexBuffer = FGE::VertexBuffer::Create( squareVertices, sizeof( squareVertices ) );

  FGE::BufferLayout layout = {

      { FGE::ShaderDataType::Float3, "a_Position" },
      { FGE::ShaderDataType::Float2, "a_TexCoord" }

  };
  m_VertexBuffer->SetLayout(layout);

  // 12/ 4 = 3 (count of indicies)
  m_IndexBuffer = FGE::IndexBuffer::Create( squareIndices, sizeof( squareIndices ) / sizeof( uint32_t ) );

  m_VertexArray->AddVertexBuffer( m_VertexBuffer );
  m_VertexArray->SetIndexBuffer( m_IndexBuffer );

  m_Shader->Bind();
  m_Texture2D->Bind();
  m_Shader->SetInt( "u_Texture", 0 );
}

void ExampleLayer::OnUpdate( FGE::Timestep ts ) {

    m_CameraController.OnUpdate( ts );

    FGE::RenderCommand::Clear();
    FGE::RenderCommand::SetClearColor( glm::vec4( 0.2f, 0.1f, 0.1f, 1.0f ) );

    FGE::Renderer::BeginScene( m_CameraController.GetCamera() );
       glm::mat4 model = glm::mat4( 1.0f );
       model = glm::translate( model, glm::vec3( 0.0f, 0.0f, -5.0f ) );
       FGE::Renderer::Submit( m_VertexArray, m_Shader, model );
    FGE::Renderer::EndScene();

}

void ExampleLayer::OnImGuiRender() {

    ImGui::Begin( "Window" );
    ImGui::Text( "This is a Text" );
    ImGui::End();

}

void ExampleLayer::OnEvent( FGE::Event& event ) {

    m_CameraController.OnEvent( event );

}
