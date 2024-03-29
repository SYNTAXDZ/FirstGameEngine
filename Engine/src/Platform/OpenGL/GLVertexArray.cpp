#include "GLVertexArray.hpp"

#include <GL/glew.h>

namespace FGE {

    static GLenum ShaderDataTypeToOpenGLBaseType( ShaderDataType type ) {
		
        switch( type ) {
			
            case ShaderDataType::Float:    return GL_FLOAT;
			case ShaderDataType::Float2:   return GL_FLOAT;
			case ShaderDataType::Float3:   return GL_FLOAT;
			case ShaderDataType::Float4:   return GL_FLOAT;
			case ShaderDataType::Mat3:     return GL_FLOAT;
			case ShaderDataType::Mat4:     return GL_FLOAT;
			case ShaderDataType::Int:      return GL_INT;
			case ShaderDataType::Int2:     return GL_INT;
			case ShaderDataType::Int3:     return GL_INT;
			case ShaderDataType::Int4:     return GL_INT;
			case ShaderDataType::Bool:     return GL_BOOL;
		
        }

		FGE_CORE_ASSERT(false, "Unknown ShaderDataType!");
		
        return 0;
	
    }

    GLVertexArray::GLVertexArray() {

        glCreateVertexArrays( 1, &m_RendererID );
        // glBindVertexArray( m_RendererID );

    }

    GLVertexArray::~GLVertexArray() {

        glDeleteVertexArrays( 1, &m_RendererID );

    }

    void GLVertexArray::Bind() const {

        glBindVertexArray( m_RendererID );

    }
    
    void GLVertexArray::UnBind() const {

        glBindVertexArray( 0 );

    }


	void GLVertexArray::AddVertexBuffer( const Ref<VertexBuffer>& vertexBuffer ) {

        FGE_CORE_ASSERT( vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!" );

        glBindVertexArray( m_RendererID );
        vertexBuffer->Bind();

        const auto& layout = vertexBuffer->GetLayout();
        for( const auto& element : layout ) {

           switch( element.Type ) {

               case ShaderDataType::Float:
               case ShaderDataType::Float2:
               case ShaderDataType::Float3:
               case ShaderDataType::Float4:
               case ShaderDataType::Int:
               case ShaderDataType::Int2:
               case ShaderDataType::Int3:
               case ShaderDataType::Int4:
               case ShaderDataType::Bool: {

                    glEnableVertexAttribArray( m_VertexBufferIndex );
                    glVertexAttribPointer( m_VertexBufferIndex, element.GetComponentCount(),
                                          ShaderDataTypeToOpenGLBaseType( element.Type ),
                                          element.Normalized? GL_TRUE : GL_FALSE,
                                          layout.GetStride(), ( const void* )( element.Offset ) );
                    m_VertexBufferIndex++;

                    break;
               
               }
               case ShaderDataType::Mat3:
               case ShaderDataType::Mat4: {
                   
                   uint8_t count = element.GetComponentCount();
                   for( uint8_t i = 0; i < count; i++ ) {

                       glEnableVertexAttribArray( m_VertexBufferIndex );
                       glVertexAttribPointer( m_VertexBufferIndex, count,
                                              ShaderDataTypeToOpenGLBaseType( element.Type ),
                                              element.Normalized? GL_TRUE : GL_FALSE,
                                              layout.GetStride(), ( const void* )( sizeof( float ) * count * i ) );
                        glVertexAttribDivisor( m_VertexBufferIndex, 1 );
                        m_VertexBufferIndex++;

                   }

                   break; 
                
                }
               
            }


        }

        m_VertexBuffers.push_back( vertexBuffer ); 

    }
    
    void GLVertexArray::SetIndexBuffer( const Ref<IndexBuffer>& indexBuffer ) {

        glBindVertexArray( m_RendererID );
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;

    }
    
} // namespace FGE
