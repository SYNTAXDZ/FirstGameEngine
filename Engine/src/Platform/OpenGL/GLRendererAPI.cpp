#include "GLRendererAPI.hpp"

#include <GL/glew.h>

namespace FGE {

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

#ifdef FGE_DEBUG
        glEnable( GL_DEBUG_OUTPUT );
        glEnable( GL_DEBUG_OUTPUT_SYNCHRONOUS );
        glDebugMessageCallback( OpenGLMessageCallback, nullptr );

        glDebugMessageControl( GL_DONT_CARE, GL_DONT_CARE,
                               GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE );
#endif

        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        //glCullFace( GL_BACK );
        glEnable( GL_DEPTH_TEST );

    }

    void GLRendererAPI::Clear() {

        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    }

    void GLRendererAPI::SetClearColor( const glm::vec4& color ) {

        glClearColor( color.r, color.g, color.b, color.a );
    }

    void GLRendererAPI::DrawIndexed( const Ref<VertexArray> &vertexArray ) {

        glDrawElements( GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr );

    }

}
