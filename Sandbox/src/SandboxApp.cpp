#include <Engine.hpp>
#include <imgui/imgui.h>

class ExampleLayer : public FGE::Layer {

public:
  ExampleLayer() : Layer( "ExampleLayer" ), m_CameraController( 800.0f / 600.0f ) {}

  virtual void OnAttach() override {

      m_VertexArray = FGE::VertexArray::Create();

      m_Shader = FGE::Shader::Create( "/home/syntax/Base/Knowledge/learn_cpp/CppProjects/FirstGameEngine/Sandbox/assets/shaders/FlatColor.glsl" );

      float vertices[] = {

        -0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
        0.0f,  0.0f,  0.5f, 0.0f

    };
    uint32_t indices[] = {0, 1, 2};

    m_VertexBuffer = FGE::VertexBuffer::Create( vertices, sizeof( vertices ) );

    FGE::BufferLayout layout = {

        {FGE::ShaderDataType::Float3, "a_Position"}

    };
    m_VertexBuffer->SetLayout( layout );

    // 12/ 4 = 3 (count of indicies)
    m_IndexBuffer = FGE::IndexBuffer::Create( indices, sizeof( indices ) / sizeof( uint32_t ) );

    m_VertexArray->AddVertexBuffer( m_VertexBuffer );
    m_VertexArray->SetIndexBuffer( m_IndexBuffer );

    m_Shader->Bind();

    glm::vec4 color = glm::vec4( 0.1f, 0.9f, 0.3f, 1.0f );
    m_Shader->SetFloat4("u_Color", color );

  }

    virtual void OnUpdate( FGE::Timestep ts ) override {

        m_CameraController.OnUpdate( ts );

        FGE::RenderCommand::Clear();
        FGE::RenderCommand::SetClearColor( glm::vec4( 0.2f, 0.3f, 0.3f, 1.0f ) );

        glm::mat4 projection = m_CameraController.GetCamera().GetProjectionMatrix();
        glm::mat4 view = m_CameraController.GetCamera().GetViewMatrix();
        glm::mat4 model = glm::mat4( 1.0f );

        m_Shader->SetMat4( "u_Projection", projection );
        m_Shader->SetMat4( "u_View", view );
        m_Shader->SetMat4( "u_Model", model );

        FGE::Renderer::BeginScene();

        FGE::Renderer::Submit( m_VertexArray, m_Shader );

        FGE::Renderer::EndScene();

    }

    virtual void OnImGuiRender() override {

        ImGui::Begin( "Window" );
        ImGui::Text( "This is a Text" );
        ImGui::End();

    }

    virtual void OnEvent( FGE::Event& event ) override {

        //FGE_TRACE( "{0}", event );

    }

private:
    FGE::Ref<FGE::VertexBuffer> m_VertexBuffer;
    FGE::Ref<FGE::IndexBuffer> m_IndexBuffer;
    FGE::Ref<FGE::VertexArray> m_VertexArray;
    FGE::CameraController m_CameraController;
    FGE::Ref<FGE::Shader> m_Shader;

};

class Sandbox : public FGE::Application {

public:
    Sandbox() {
        // Push The Layer To The Stack of Layers
        PushLayer( new ExampleLayer() );

    }
    ~Sandbox() {}

};

FGE::Application* FGE::CreateApplication() {

    return new Sandbox();

}


