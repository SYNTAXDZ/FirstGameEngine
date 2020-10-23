#include "GLRendererAPI.hpp"

#include <GL/glew.h>

namespace FGE {
void APIENTRY glDebugOutput(GLenum source, 
                            GLenum type, 
                            unsigned int id, 
                            GLenum severity, 
                            GLsizei length, 
                            const char *message, 
                            const void *userParam)
{
    // ignore non-significant error/warning codes
    if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; 

    std::cout << "---------------" << std::endl;
    std::cout << "Debug message (" << id << "): " <<  message << std::endl;

    switch (source)
    {
        case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
        case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
        case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
        case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
        case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
    } std::cout << std::endl;

    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break; 
        case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
        case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
        case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
        case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
        case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
        case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
    } std::cout << std::endl;
    
    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
        case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
        case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
        case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
    } std::cout << std::endl;
    std::cout << std::endl;
}
    void OpenGLMessageCallback(unsigned source, unsigned type, unsigned id,
                           unsigned severity, int length, const char *message,
                           const void *userParam) {
        switch( severity ) {

            case GL_DEBUG_SEVERITY_HIGH:
                FGE_CORE_CRITICAL( message );
                return;
            case GL_DEBUG_SEVERITY_MEDIUM:
                FGE_CORE_ERROR( message );
                return;
            case GL_DEBUG_SEVERITY_LOW:
                FGE_CORE_WARN( message );
                return;
            case GL_DEBUG_SEVERITY_NOTIFICATION:
                FGE_CORE_TRACE( message );
                return;

        }

        FGE_CORE_ASSERT( false, "Unknown severity level!" );

    }

    void GLRendererAPI::Init() {

        // glEnable( GL_DEBUG_OUTPUT );
        // glEnable( GL_DEBUG_OUTPUT_SYNCHRONOUS );
        // glDebugMessageCallback( OpenGLMessageCallback, nullptr );

        // glDebugMessageControl( GL_DONT_CARE, GL_DONT_CARE,
                               // GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE );
        int flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
          glEnable(GL_DEBUG_OUTPUT);
          glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
          glDebugMessageCallback(glDebugOutput, nullptr);
          glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0,
                                nullptr, GL_TRUE);
          glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_ERROR,
                               0, GL_DEBUG_SEVERITY_MEDIUM, -1,
                               "error message here");
        }
        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        //glCullFace( GL_BACK );
        glEnable( GL_DEPTH_TEST );

    }

    void GLRendererAPI::Clear() {

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    }

    void GLRendererAPI::SetViewport( uint32_t width, uint32_t height ) {

        glViewport( 0, 0, width, height );

    }

    void GLRendererAPI::SetClearColor( const glm::vec4& color ) {

        glClearColor( color.r, color.g, color.b, color.a );
    }

    void GLRendererAPI::DrawIndexed( const Ref<VertexArray> &vertexArray ) {

        glDrawElements( GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr );

    }

}
