#include "ExampleLayer.hpp"

#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GL/glew.h>

ExampleLayer::ExampleLayer() : Layer( "ExampleLayer" ), m_CameraController( 800.0f / 600.0f ) {

    m_VertexArray = FGE::VertexArray::Create();

    m_Shader = FGE::Shader::Create(
                                   "/home/syntax/Base/Knowledge/learn_cpp/CppProjects/FirstGameEngine/"
                                   "Sandbox/assets/shaders/Texture.glsl");

    m_ChrenoShader = FGE::Shader::Create(
        "/home/syntax/Base/Knowledge/learn_cpp/CppProjects/FirstGameEngine/"
        "Sandbox/assets/shaders/Texture.glsl");

    m_Texture2D = FGE::Texture2D::Create(
                                         "/home/syntax/Base/Knowledge/learn_cpp/CppProjects/FirstGameEngine/"
                                         "Sandbox/assets/textures/Checkerboard.png");

    m_ChrenoTexture2D = FGE::Texture2D::Create(
        "/home/syntax/Base/Knowledge/learn_cpp/CppProjects/FirstGameEngine/"
        "Sandbox/assets/textures/ChernoLogo.png" );

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

// ------------------------------------------------------------------
    float cubeVertices[] = {
        // positions          // normals           // texture coords
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };
    float cube_vertices[] = {
        // Front face
        -1.0, -1.0, 1.0,  0.0f,  0.0f,
        1.0, -1.0, 1.0,   1.0f,  0.0f,
        1.0, 1.0, 1.0,    1.0f,  1.0f,
        -1.0, 1.0, 1.0,   0.0f,  1.0f,
        // Back face
        -1.0, -1.0, -1.0, 0.0f, 0.0f,
        -1.0, 1.0, -1.0,  0.0f, 1.0f,
        1.0, 1.0, -1.0,   1.0f, 1.0f,
        1.0, -1.0, -1.0,  1.0f, 0.0f,

        // Top face
        -1.0, 1.0, -1.0, 0.0f, 1.0f,
        -1.0, 1.0, 1.0,  0.0f, 1.0f,
        1.0, 1.0, 1.0,   1.0f, 1.0f,
        1.0, 1.0, -1.0,  1.0f, 1.0f,

        // Bottom face
        -1.0, -1.0, -1.0, 0.0f, 0.0f,
        1.0, -1.0, -1.0,  1.0f, 0.0f,
        1.0, -1.0, 1.0,   1.0f, 0.0f,
        -1.0, -1.0, 1.0,  0.0f, 0.0f,

        // Right face
        1.0, -1.0, -1.0, 1.0f, 0.0f,
        1.0, 1.0, -1.0,  1.0f, 1.0f,
        1.0, 1.0, 1.0,   1.0f, 1.0f,
        1.0, -1.0, 1.0,  1.0f, 0.0f,

        // Left face
        -1.0, -1.0, -1.0, 0.0f, 0.0f,
        -1.0, -1.0, 1.0, 0.0f, 0.0f,
        -1.0, 1.0, 1.0,  0.0f, 1.0f,
        -1.0, 1.0, -1.0, 0.0f, 1.0f,
    };

    uint32_t indices[] = {0, 1, 2};
    uint32_t squareIndices[] = {0, 1, 2, 2, 3, 0 };
    uint32_t cubeIndices[] = {
        0,  1,  2,  0,  2,  3,  // front
        4,  5,  6,  4,  6,  7,  // back
        8,  9,  10, 8,  10, 11, // top
        12, 13, 14, 12, 14, 15, // bottom
        16, 17, 18, 16, 18, 19, // right
        20, 21, 22, 20, 22, 23, // left
    };
    m_VertexBuffer = FGE::VertexBuffer::Create( cube_vertices, sizeof( cube_vertices ) );

    FGE::BufferLayout layout = {

        { FGE::ShaderDataType::Float3, "a_Position" },
        // { FGE::ShaderDataType::Float3, "a_Normal" },
        { FGE::ShaderDataType::Float2, "a_TexCoord" }

    };
    m_VertexBuffer->SetLayout(layout);

  // 12/ 4 = 3 (count of indicies)
  m_IndexBuffer = FGE::IndexBuffer::Create( cubeIndices, sizeof( cubeIndices ) / sizeof( uint32_t ) );

  m_VertexArray->AddVertexBuffer( m_VertexBuffer );
  m_VertexArray->SetIndexBuffer( m_IndexBuffer );

  m_Shader->Bind();
  m_Shader->SetInt( "u_Texture", 0 );

  m_ChrenoShader->Bind();
  m_ChrenoShader->SetInt("u_Texture", 0);

}

void ExampleLayer::OnUpdate( FGE::Timestep ts ) {

    m_CameraController.OnUpdate( ts );

    FGE::RenderCommand::Clear();
    FGE::RenderCommand::SetClearColor( glm::vec4( 0.2f, 0.1f, 0.1f, 1.0f ) );

    FGE::Renderer::BeginScene( m_CameraController.GetCamera() );
       glm::mat4 model = glm::mat4( 1.0f );
       model = glm::translate( model, glm::vec3( 0.0f, 0.0f, -5.0f ) );
       m_Texture2D->Bind();
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
