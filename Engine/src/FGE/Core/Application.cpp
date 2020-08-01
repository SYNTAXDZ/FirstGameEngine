#include "Application.hpp"
#include "Base.hpp"
#include "Log.hpp"
#include "Input.hpp"

#include <GL/glew.h>

#define BIND_EVENT_FN( x ) std::bind( &Application::x, this, std::placeholders::_1 )

namespace FGE {

    Application* Application::s_Instance = nullptr;

    Application::Application() {

        FGE_CORE_ASSERT( !s_Instance, "Application already exists!" );
		s_Instance = this;

        // Create The Window
        m_Window =  std::unique_ptr<Window>( Window::Create() );
        // Set The EventCallback To Handle The Events
        m_Window->SetEventCallback( BIND_EVENT_FN( OnEvent ) );

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay( m_ImGuiLayer );

        glCreateVertexArrays( 1, &m_VAO );
        glBindVertexArray( m_VAO );
        glCreateBuffers( 1, &m_VBO );
        glBindBuffer( GL_ARRAY_BUFFER, m_VBO );

        float vertices[] = {

            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f

        };
        unsigned int indices[] = { 0, 1, 2 };

        glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), nullptr );

        glCreateBuffers( 1, &m_IBO );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );

        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );

        

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

            glClear( GL_COLOR_BUFFER_BIT );
            glClearColor( 0.6f, 0.5f, 0.5f, 1.0f );

            glBindVertexArray( m_VAO );
            glDrawElements( GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr );

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