#include "GLGraphicsContext.hpp"

#include "FGE/Core/Log.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace FGE {

    GLGraphicsContext::GLGraphicsContext( GLFWwindow* windowHandle ) 
        : m_WindowHandle( windowHandle ) {

        glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
        glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 5 );
        glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    }

    void GLGraphicsContext::Init() {

        glfwMakeContextCurrent( m_WindowHandle );

        glewExperimental = GL_TRUE;
        GLenum status = glewInit();
        FGE_CORE_ASSERT( !status, "Failed To Load GLEW !!" );

        FGE_CORE_INFO( "OpenGL Info:" );
		FGE_CORE_INFO( "  Vendor: {0}", glGetString( GL_VENDOR ) );
		FGE_CORE_INFO( "  Renderer: {0}", glGetString( GL_RENDERER ) );
		FGE_CORE_INFO( "  Version: {0}", glGetString( GL_VERSION ) );

    }

    void GLGraphicsContext::SwapBuffers() {

        glfwSwapBuffers( m_WindowHandle );

    }

} // namespace FGE
