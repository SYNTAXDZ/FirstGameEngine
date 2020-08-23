#include "Window.hpp"
#include "Log.hpp"
#include "Input.hpp"

#include <GLFW/glfw3.h>

#include "FGE/Events/ApplicationEvent.hpp"
#include "FGE/Events/MouseEvent.hpp"
#include "FGE/Events/KeyEvent.hpp"

//#include "Platform/OpenGL/GLGraphicsContext.hpp"

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

        m_Context = GraphicsContext::Create( m_Window );
        m_Context->Init();

        glfwSetWindowUserPointer( m_Window, &m_Data );
        SetVSync( true );

        glfwSetWindowSizeCallback( m_Window, []( GLFWwindow* window, int width, int height ) {

            WindowData& data = *( WindowData* )glfwGetWindowUserPointer( window );
            data.Width = width;
            data.Height = height;

            WindowResizeEvent event( width, height );

            data.EventCallback( event );

        } );

        glfwSetWindowCloseCallback( m_Window, []( GLFWwindow* window ) {

            WindowData& data = *( WindowData* )glfwGetWindowUserPointer( window );
            WindowCloseEvent event;
            data.EventCallback( event );

        } );

        glfwSetKeyCallback( m_Window, []( GLFWwindow* window, int key, int scancode, int action, int mods ) {

            WindowData& data = *( WindowData* )glfwGetWindowUserPointer( window );

            switch( action ) {
				// if the key is pressed set The EventCallback to the KeyPressedEvent
                case GLFW_PRESS:
                    {
                        KeyPressedEvent event( static_cast<KeyCode>( key ), 0 );
                        data.EventCallback( event );

                        break;
                    }
                case GLFW_RELEASE:
                    {
                        KeyReleasedEvent event( static_cast<KeyCode>( key ) );
                        data.EventCallback( event );

                        break;
                    }
                case GLFW_REPEAT:
                    {
                        KeyPressedEvent event( static_cast<KeyCode>( key ), 1 );
                        data.EventCallback( event );

                        break;
                    }

            }

        } );

        glfwSetMouseButtonCallback( m_Window, []( GLFWwindow* window, int button, int action, int mods ) {

            WindowData& data = *( WindowData* )glfwGetWindowUserPointer( window );

            switch( action ) {

                case GLFW_PRESS:
                    {
                        MouseButtonPressedEvent event( static_cast<MouseCode>( button ));
                        data.EventCallback( event );

                        break;
                    }
                case GLFW_RELEASE:
                    {
                        MouseButtonReleasedEvent event( static_cast<MouseCode>( button ) );
                        data.EventCallback( event );

                        break;
                    }
            }

        } );

        glfwSetScrollCallback( m_Window, []( GLFWwindow* window, double xOffset, double yOffset ) {

            WindowData& data = *( WindowData* )glfwGetWindowUserPointer( window );

            MouseScrolledEvent event( ( float )xOffset, ( float )yOffset );
            data.EventCallback( event );

        } );

        glfwSetCursorPosCallback( m_Window, []( GLFWwindow* window, double xPos, double yPos ) {

            WindowData& data = *( WindowData* )glfwGetWindowUserPointer( window );

            MouseMovedEvent event( ( float )xPos, ( float )yPos );

            data.EventCallback( event );

        } );

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
        m_Context->SwapBuffers();

    }

    Window* Window::Create( const WindowProps& props ) {

        return new Window( props );

    }

}
