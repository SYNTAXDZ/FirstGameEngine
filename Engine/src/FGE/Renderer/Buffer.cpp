
#include "Buffer.hpp"
#include "Platform/OpenGL/GLBuffer.hpp"

#include "Renderer.hpp"

#include "FGE/Core/Log.hpp"

namespace FGE {

    // Ref<VertexBuffer> VertexBuffer::Create( uint32_t size ) {} 

    Ref<VertexBuffer> VertexBuffer::Create( float* vertices, uint32_t size ) {

        // Check for The Renderering API
        switch( Renderer::GetAPI() ) {
        
            case RendererAPI::API::None:

                FGE_CORE_ASSERT( false, "No API was Selected !!" );            
                return nullptr;
            // if its OpenGL so Create The GL Version of VertexBuffer        
            case RendererAPI::API::OpenGL:
            
                return CreateRef<GLVertexBuffer>( vertices, size );
            
            default:
                break;
        
        }

        FGE_CORE_CRITICAL( "No Available API for Rendering !!" );
        return nullptr;

    } 
    

	Ref<IndexBuffer> IndexBuffer::Create( uint32_t* indices, uint32_t count ) {

        switch( Renderer::GetAPI() ) {
        
            case RendererAPI::API::None:

               FGE_CORE_ASSERT( false, "No API was Selected !!" );            
                return nullptr;
        
            case RendererAPI::API::OpenGL:
            
                return CreateRef<GLIndexBuffer>( indices, count );
            
            default:
                break;
        
        }

        FGE_CORE_CRITICAL( "No Available API for Rendering !!" );
        return nullptr;

    }
    
} // namespace FGE
