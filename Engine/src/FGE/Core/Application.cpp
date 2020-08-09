#include "Application.hpp"
#include "Base.hpp"
#include "Log.hpp"
#include "Input.hpp"

#include "FGE/Renderer/Renderer.hpp"

#define BIND_EVENT_FN( x ) std::bind( &Application::x, this, std::placeholders::_1 )

namespace FGE {

    Application* Application::s_Instance = nullptr;

    Application::Application() {

        FGE_CORE_ASSERT( !s_Instance, "Application already exists!" );
        // set the instance to this instance
        s_Instance = this;

        // Create The Window
        m_Window =  std::unique_ptr<Window>( Window::Create() );
        // Set The EventCallback To Handle The Events
        m_Window->SetEventCallback( BIND_EVENT_FN( OnEvent ) );

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay( m_ImGuiLayer );

        m_VertexArray = VertexArray::Create();

        float vertices[] = {

            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f

        };
        uint32_t indices[] = { 0, 1, 2 };

        m_VertexBuffer = VertexBuffer::Create( vertices, sizeof( vertices ) );

        BufferLayout layout = {

            { ShaderDataType::Float3, "a_Position" }

        };
        m_VertexBuffer->SetLayout( layout );
        
        // 12/ 4 = 3 (count of indicies)
        m_IndexBuffer = IndexBuffer::Create( indices, sizeof( indices )/ sizeof( uint32_t ) );

        m_VertexArray->AddVertexBuffer( m_VertexBuffer );
        m_VertexArray->SetIndexBuffer( m_IndexBuffer );

    }
    
    Application::~Application() {}

    void Application::OnEvent( Event& e ) {

        // Dispatch The Event Based On His Type
        EventDispatcher dispatcher( e );
        dispatcher.Dispatch<WindowCloseEvent>( BIND_EVENT_FN( OnWindowClose ) );

        // in This Loop We Go from The last Layer In LayerStack to The First One
        for( auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it ) {
            // If The Event Is Handled, So Break
            if( e.Handled ) 
				break;
			// Handle The Events from Last Layer to The First One
            ( *it )->OnEvent( e );
		}

    }

    // PushLayer: Add The Layer To LayerStack, And Attach It
    void Application::PushLayer( Layer* layer ) {

        m_LayerStack.PushLayer( layer );
        layer->OnAttach();

    }

    void Application::PushOverlay( Layer* overlay ) {

        m_LayerStack.PushOverlay( overlay );
        overlay->OnAttach();

    }
    
    void Application::Run() {

        while( m_Running ) {

            RenderCommand::Clear();
            RenderCommand::SetClearColor( glm::vec4( 0.6f, 0.5f, 0.5f, 1.0f ) );

            Renderer::BeginScene();

            m_VertexArray->Bind();
            Renderer::Submit( m_VertexArray );

            Renderer::EndScene();

            // Because We Added Implimentation for begin() and end() we can use
            // the foreach array like this
            for( Layer* layer : m_LayerStack )
                layer->OnUpdate();

            m_ImGuiLayer->Begin();
            for( Layer* layer : m_LayerStack )
                layer->OnImGuiRender();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();

            if( Input::IsKeyPressed( FGE_KEY_ESCAPE ) )
                m_Running = false;

        }
        

    }

    bool Application::OnWindowClose( WindowCloseEvent& e ) {

        m_Running = false;

        return true;

    }


}
