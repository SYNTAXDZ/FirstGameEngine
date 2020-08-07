#include "VertexArray.hpp"
#include "Platform/OpenGL/GLVertexArray.hpp"

#include "Renderer.hpp"

#include "FGE/Core/Log.hpp"

namespace FGE {

    Ref<VertexArray> VertexArray::Create() {

        switch( Renderer::GetAPI() ) {
        
            case RendererAPI::None:

                FGE_CORE_ASSERT( false, "Unknown API for The Renderer !" );
                return nullptr;
            
            case RendererAPI::OpenGL:

                return CreateRef<GLVertexArray>();
        
        }

        FGE_CORE_ASSERT( false, "No API Specified !!" );
        return nullptr;

    }
    
} // namespace FGE
