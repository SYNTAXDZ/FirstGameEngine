#include "Application.hpp"
#include "Base.hpp"
#include "Log.hpp"

#define BIND_EVENT_FN( x ) std::bind( &Application::x, this, std::placeholders::_1 )

namespace FGE {

    Application::Application() {

        // Create The Window
        m_Window =  std::unique_ptr<Window>( Window::Create() );
        // Set The EventCallback To Handle The Events
        m_Window->SetEventCallback( BIND_EVENT_FN( OnEvent ) );

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

            for( Layer* layer : m_LayerStack )
                layer->OnUpdate();

            m_Window->OnUpdate();

        }
        

    }

    bool Application::OnWindowClose( WindowCloseEvent& e ) {

        m_Running = false;

        return true;

    }


}