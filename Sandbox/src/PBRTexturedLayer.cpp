#include "PBRTexturedLayer.hpp"
#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

PBRLayer::PBRLayer() : Layer( "PBRLayer" ), m_CameraController( 800.0f / 600.0f ) {

  // lights
  // ------
  m_LightPositions = {
      glm::vec3(-10.0f, 10.0f, 10.0f),
      glm::vec3(10.0f, 10.0f, 10.0f),
      glm::vec3(-10.0f, -10.0f, 10.0f),
      glm::vec3(10.0f, -10.0f, 10.0f),
  };
  m_LightColors = {
      glm::vec3(300.0f, 300.0f, 300.0f), glm::vec3(300.0f, 300.0f, 300.0f),
      glm::vec3(300.0f, 300.0f, 300.0f), glm::vec3(300.0f, 300.0f, 300.0f)
  };

  int nrRows = 7;
  int nrColumns = 7;
  float spacing = 2.5;

  m_VertexArray = FGE::VertexArray::Create();

  m_PBRShader = FGE::Shader::Create(
      "/home/syntax/Base/Knowledge/learn_cpp/CppProjects/FirstGameEngine/"
      "Sandbox/assets/shaders/PBRTextured.glsl");

  m_AlbedoTexture = FGE::Texture2D::Create(
                                       "/home/syntax/Base/Knowledge/learn_cpp/CppProjects/FirstGameEngine/"
                                       "Sandbox/assets/textures/pbr/rusted_iron/albedo.png");

  m_NormalTexture = FGE::Texture2D::Create(
      "/home/syntax/Base/Knowledge/learn_cpp/CppProjects/FirstGameEngine/"
      "Sandbox/assets/textures/pbr/rusted_iron/normal.png");

  m_MetallicTexture = FGE::Texture2D::Create(
      "/home/syntax/Base/Knowledge/learn_cpp/CppProjects/FirstGameEngine/"
      "Sandbox/assets/textures/pbr/rusted_iron/metallic.png");

  m_RoughnessTexture = FGE::Texture2D::Create(
      "/home/syntax/Base/Knowledge/learn_cpp/CppProjects/FirstGameEngine/"
      "Sandbox/assets/textures/pbr/rusted_iron/roughness.png");

  m_AOTexture = FGE::Texture2D::Create(
      "/home/syntax/Base/Knowledge/learn_cpp/CppProjects/FirstGameEngine/"
      "Sandbox/assets/textures/pbr/rusted_iron/ao.png");

    glm::mat4 model = glm::mat4( 1.0f );
    model = glm::translate( model, glm::vec3( 0.0f, 0.0f, -5.0f ) );
    m_Sphere = FGE::Sphere::Create( m_PBRShader, model );

}

void PBRLayer::OnAttach() {

    float cube_vertices[] = {
        // Front face
        -1.0, -1.0, 1.0, 0.0f, 0.0f, 1.0f,  0.0f,  0.0f,
        1.0, -1.0, 1.0, 0.0f, 0.0f, 1.0f,   1.0f,  0.0f,
        1.0, 1.0, 1.0, 0.0f, 0.0f, 1.0f,    1.0f,  1.0f,
        -1.0, 1.0, 1.0, 0.0f, 0.0f, 1.0f,   0.0f,  1.0f,
        // Back face
        -1.0, -1.0, -1.0, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -1.0, 1.0, -1.0, 0.0f, 0.0f, -1.0f,  0.0f, 1.0f,
        1.0, 1.0, -1.0, 0.0f, 0.0f, -1.0f,   1.0f, 1.0f,
        1.0, -1.0, -1.0, 0.0f, 0.0f, -1.0f,  1.0f, 0.0f,

        // Top face
        -1.0, 1.0, -1.0, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -1.0, 1.0, 1.0, 0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        1.0, 1.0, 1.0, 0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
        1.0, 1.0, -1.0, 0.0f, 1.0f, 0.0f,  1.0f, 1.0f,

        // Bottom face
        -1.0, -1.0, -1.0, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        1.0, -1.0, -1.0, 0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
        1.0, -1.0, 1.0, 0.0f, -1.0f, 0.0f,   1.0f, 0.0f,
        -1.0, -1.0, 1.0, 0.0f, -1.0f, 0.0f,  0.0f, 0.0f,

        // Right face
        1.0, -1.0, -1.0, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        1.0, 1.0, -1.0, 1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        1.0, 1.0, 1.0, 1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
        1.0, -1.0, 1.0, 1.0f, 0.0f, 0.0f,  1.0f, 0.0f,

        // Left face
        -1.0, -1.0, -1.0, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -1.0, -1.0, 1.0, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -1.0, 1.0, 1.0, -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        -1.0, 1.0, -1.0, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

    };

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

        {FGE::ShaderDataType::Float3, "a_Position"},
        {FGE::ShaderDataType::Float3, "a_Normal"},
        {FGE::ShaderDataType::Float2, "a_TexCoords"},

    };
    m_VertexBuffer->SetLayout(layout);

    // 12/ 4 = 3 (count of indicies)
    m_IndexBuffer = FGE::IndexBuffer::Create( cubeIndices, sizeof( cubeIndices ) / sizeof( uint32_t ) );

    m_VertexArray->AddVertexBuffer( m_VertexBuffer );
    m_VertexArray->SetIndexBuffer( m_IndexBuffer );

    m_Sphere->SetData();

}

void PBRLayer::OnUpdate( FGE::Timestep ts ) {

    m_CameraController.OnUpdate( ts );

    FGE::RenderCommand::Clear();
    FGE::RenderCommand::SetClearColor( glm::vec4( 0.2f, 0.1f, 0.1f, 1.0f ) );

    FGE::Renderer::BeginScene( m_CameraController.GetCamera() );
       glm::mat4 model = glm::mat4( 1.0f );
       model = glm::translate( model, glm::vec3( 0.0f, 0.0f, -5.0f ) );

       m_PBRShader->Bind();
       m_PBRShader->SetInt("u_AlbedoMap", 0);
       m_PBRShader->SetInt("u_NormalMap", 1);
       m_PBRShader->SetInt("u_MetallicMap", 2);
       m_PBRShader->SetInt("u_RoughnessMap", 3);
       m_PBRShader->SetInt("u_AOMap", 4);
       m_AlbedoTexture->Bind(0);
       m_NormalTexture->Bind(1);
       m_MetallicTexture->Bind(2);
       m_RoughnessTexture->Bind(3);
       m_AOTexture->Bind(4);

       m_PBRShader->SetFloat3("u_CamPos", m_CameraController.GetCamera().GetPosition());
       //FGE::Renderer::Submit( m_VertexArray, m_PBRShader, model );
       m_Sphere->Draw();
       FGE::Renderer::EndScene();

   FGE::Renderer::BeginScene( m_CameraController.GetCamera() );

   // render light source (simply re-render sphere at light positions)
   // this looks a bit off as we use the same shader, but it'll make their
   // positions obvious and keeps the codeprint small.
   for (unsigned int i = 0; i < m_LightPositions.size() / sizeof( m_LightPositions[0] ); ++i) {

       glm::vec3 newPos = m_LightPositions[i];

       m_PBRShader->SetFloat3("lightPositions[" + std::to_string(i) + "]",
                            newPos);

       m_PBRShader->SetFloat3("lightColors[" + std::to_string(i) + "]",
                            m_LightColors[i]);

       model = glm::mat4( 1.0f );
       model = glm::translate( model, newPos );
       model = glm::scale( model, glm::vec3( 0.5f ) );
       FGE::Renderer::Submit( m_VertexArray, m_PBRShader, model );

   }

   FGE::Renderer::EndScene();

}

void PBRLayer::OnImGuiRender() {

    ImGui::Begin( "Window" );
    ImGui::Text( "This is a Text" );
    ImGui::End();

}

void PBRLayer::OnEvent( FGE::Event& event ) {

    m_CameraController.OnEvent( event );

}
