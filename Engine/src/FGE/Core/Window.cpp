#include "Window.hpp"
#include "Log.hpp"

#include "FGE/Events/ApplicationEvent.hpp"
#include "FGE/Events/MouseEvent.hpp"
#include "FGE/Events/KeyEvent.hpp"

namespace FGE {

    static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback( int error, const char* description ) {
		
        FGE_CORE_ERROR( "GLFW Error ({0}): {1}", error, description) ;
	
    }

    Window::Window( const WindowProps& props ) {

        Init( props );

    }

    Window::~Window() {

        Shutdown();

    }

    void Window::Init( const WindowProps& props ) {

        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        if( s_GLFWWindowCount == 0 ) {
			
            int success = glfwInit();
			
            FGE_CORE_ASSERT( success, "Could not initialize GLFW!" );
			
            glfwSetErrorCallback( GLFWErrorCallback );
		
        }        

        m_Window = glfwCreateWindow( (int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr );
		++s_GLFWWindowCount;

        glfwMakeContextCurrent( m_Window );

        // Init GLEW
        glewExperimental = GL_TRUE;
        if( glewInit() != GLEW_OK ) {

            std::cout << "Unable To Init GLEW";

            glfwTerminate();

        }

        glfwSetWindowUserPointer( m_Window, &m_Data );
		SetVSync( true );

    }

    void Window::Shutdown() {

        glfwDestroyWindow( m_Window );
        --s_GLFWWindowCount;

        if( s_GLFWWindowCount == 0 ) {
			
            glfwTerminate();
		
        }

    }

    void Window::SetVSync( bool enabled ) {

        if( enabled )
            glfwSwapInterval( 1 );
        else
            glfwSwapInterval( 0 );

        m_Data.VSync = enabled;

    }

    void Window::OnUpdate() {

        glfwPollEvents();
        glfwSwapBuffers( m_Window );

    }

    Window* Window::Create( const WindowProps& props ) {

        return new Window( props );

    }

}