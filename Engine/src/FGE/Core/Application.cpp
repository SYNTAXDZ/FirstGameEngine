#include "Application.hpp"
#include "Base.hpp"
#include "Log.hpp"

#include "FGE/Events/ApplicationEvent.hpp"
#include "FGE/Events/MouseEvent.hpp"
#include "FGE/Events/KeyEvent.hpp"

namespace FGE {

    Application::Application() {

        m_Window =  std::unique_ptr<Window>( Window::Create() );

    }
    Application::~Application() {}

    void Application::Run() {

        while( m_Running ) {
            
            m_Window->OnUpdate();

        }
        

    }


}