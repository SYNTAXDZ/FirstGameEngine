
#include "SimpleLayer.hpp"
#include "Utils.hpp"

#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


SimpleLayer::SimpleLayer() : Layer( "SimpleLayer" ), m_CameraController( 800.0f / 600.0f ) {

    // creation of vertexArrays
    m_VertexArray = FGE::VertexArray::Create();
    m_LightVertexArray = FGE::VertexArray::Create();

    m_Shader = FGE::Shader::Create(
                                   "/home/syntax/Base/Knowledge/learn_cpp/FirstGameEngine/"
                                   "Sandbox/assets/shaders/Simple.glsl");

    // creation of shaders
    m_LightShader = FGE::Shader::Create(
                                   "/home/syntax/Base/Knowledge/learn_cpp/FirstGameEngine/"
                                   "Sandbox/assets/shaders/Light.glsl");

    m_Texture2D = FGE::Texture2D::Create(
                                         "/home/syntax/Base/Knowledge/learn_cpp/FirstGameEngine/"
                                         "Sandbox/assets/textures/Checkerboard.png");

}

void SimpleLayer::OnAttach() {

    m_VertexBuffer = FGE::VertexBuffer::Create( cube_vertices, sizeof( cube_vertices ) );
    m_LightVertexBuffer = FGE::VertexBuffer::Create( box_vertices, sizeof( box_vertices ) );

    FGE::BufferLayout layout = {

        { FGE::ShaderDataType::Float3, "a_Position" },
        { FGE::ShaderDataType::Float3, "a_Normal" },
        { FGE::ShaderDataType::Float2, "a_TexCoord" }

    };
    m_VertexBuffer->SetLayout(layout);


    FGE::BufferLayout boxLayout = {

        { FGE::ShaderDataType::Float3, "a_Position" },

    };
    m_LightVertexBuffer->SetLayout( boxLayout );

  // 12/ 4 = 3 (count of indicies)
  m_IndexBuffer = FGE::IndexBuffer::Create( cube_indices, sizeof( cube_indices ) / sizeof( uint32_t ) );
  m_LightIndexBuffer = FGE::IndexBuffer::Create( cube_indices, sizeof( cube_indices ) / sizeof( uint32_t ) );

  m_VertexArray->AddVertexBuffer( m_VertexBuffer );
  m_LightVertexArray->AddVertexBuffer( m_LightVertexBuffer );
  m_VertexArray->SetIndexBuffer( m_IndexBuffer );
  m_LightVertexArray->SetIndexBuffer( m_LightIndexBuffer );

  //m_Shader->Bind();
  //m_Shader->SetInt( "u_Texture", 0 );
  m_Shader->Bind();
  m_Shader->SetFloat3( "objectColor", glm::vec3( 1.0f, 0.5f, 0.3f ) );
  m_Shader->SetFloat3( "lightColor", glm::vec3( 1.0f, 1.0f, 1.0f ) );
  m_Shader->SetFloat3( "u_LightPos", m_LightPos );

}

void SimpleLayer::OnUpdate( FGE::Timestep ts ) {

    m_CameraController.OnUpdate( ts );

    FGE::RenderCommand::Clear();
    FGE::RenderCommand::SetClearColor( glm::vec4( 0.08f, 0.08f, 0.08f, 1.0f ) );

    FGE::Renderer::BeginScene( m_CameraController.GetCamera() );
       glm::mat4 model = glm::mat4( 1.0f );
       model = glm::translate( model, glm::vec3( 0.0f, 0.0f, -5.0f ) );
       m_Shader->Bind();
       m_Shader->SetFloat3( "u_ViewPos", m_CameraController.GetCamera().GetPosition() );
       FGE::Renderer::Submit( m_VertexArray, m_Shader, model );
       // this object represent the light source
       model = glm::translate( model, m_LightPos );
       model = glm::scale( model, glm::vec3( 0.2f ) );
       FGE::Renderer::Submit( m_LightVertexArray, m_LightShader, model );
   FGE::Renderer::EndScene();

}

void SimpleLayer::OnImGuiRender() {

    ImGui::Begin( "Window" );
    ImGui::Text( "This is a Text" );
    ImGui::End();

}

void SimpleLayer::OnEvent( FGE::Event& event ) {

    m_CameraController.OnEvent( event );

}
