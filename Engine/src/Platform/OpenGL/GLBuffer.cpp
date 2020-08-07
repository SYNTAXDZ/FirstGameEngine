
#include "GLBuffer.hpp"

#include <GL/glew.h>

namespace FGE {

    /////////////////////////////////////////////////////////////////////////////////////
    ////////// VertexBuffer /////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////

   // Create The Vertex Buffer
    GLVertexBuffer::GLVertexBuffer( float* vertices, uint32_t size ) {

        glCreateBuffers( 1, &m_RendererID );
        glBindBuffer( GL_ARRAY_BUFFER, m_RendererID );

        glBufferData( GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW );

    }

    GLVertexBuffer::~GLVertexBuffer() {

        glDeleteBuffers( 1, &m_RendererID );

    }
    
    void GLVertexBuffer::Bind() const {

        glBindBuffer( GL_ARRAY_BUFFER, m_RendererID );

    }


    void GLVertexBuffer::UnBind() const {

        glBindBuffer( GL_ARRAY_BUFFER, 0 );

    }

    /////////////////////////////////////////////////////////////////////////////////////
    ////////// IndexBuffer //////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////

  // Create The IndexBuffer
    GLIndexBuffer::GLIndexBuffer( uint32_t* indices, uint32_t count ) : m_Count( count ) {

        glCreateBuffers( 1, &m_RendererID );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_RendererID );

        glBufferData( GL_ELEMENT_ARRAY_BUFFER, count * sizeof( uint32_t ), indices, GL_STATIC_DRAW );

    }

    GLIndexBuffer::~GLIndexBuffer() {

        glDeleteBuffers( 1, &m_RendererID );

    }

    void GLIndexBuffer::Bind() const {

        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_RendererID );

    }


    void GLIndexBuffer::UnBind() const {

        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

    }

} // namespace FGE
