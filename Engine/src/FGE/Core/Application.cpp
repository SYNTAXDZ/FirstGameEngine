#include "Application.hpp"
#include "Base.hpp"
#include "Log.hpp"
#include "Input.hpp"

#include "FGE/Renderer/Renderer.hpp"

#include <GLFW/glfw3.h>

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

        Renderer::Init();

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay( m_ImGuiLayer );

    }

    Application::~Application() {

        Renderer::Shutdown();

    }

    void Application::OnEvent( Event& e ) {

        // Dispatch The Event Based On His Type
        EventDispatcher dispatcher( e );
        dispatcher.Dispatch<WindowCloseEvent>( BIND_EVENT_FN( OnWindowClose ) );
        dispatcher.Dispatch<WindowResizeEvent>( BIND_EVENT_FN( OnWindowResize ) );

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

            float time = ( float )glfwGetTime();
            Timestep timestep = time - m_LastFrameTime;
            m_LastFrameTime = time;

            if( !m_Minimized ) {

                // Because We Added Implimentation for begin() and end() we can
                // use the foreach array like this
                for( Layer *layer : m_LayerStack )
                    layer->OnUpdate( timestep );

                m_ImGuiLayer->Begin();
                for( Layer *layer : m_LayerStack )
                    layer->OnImGuiRender();
                m_ImGuiLayer->End();

            }
            m_Window->OnUpdate();

            if( Input::IsKeyPressed( FGE_KEY_ESCAPE ) )
                m_Running = false;

        }

    }

    bool Application::OnWindowClose( WindowCloseEvent& e ) {

        m_Running = false;

        return true;

    }

    bool Application::OnWindowResize( WindowResizeEvent &e ) {

        if( e.GetWidth() == 0 || e.GetHeight() == 0 ) {

            m_Minimized = true;

            return false;

        }

        m_Minimized = false;

        Renderer::OnWindowResize( e.GetWidth(), e.GetHeight() );

        return true;

    }
}
