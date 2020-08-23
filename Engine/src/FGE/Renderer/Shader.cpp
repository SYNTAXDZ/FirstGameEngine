#include "Shader.hpp"
#include "Renderer.hpp"

#include "Platform/OpenGL/GLShader.hpp"

namespace FGE {
    

    Ref<Shader> Shader::Create( const std::string& filepath ) {

        switch( Renderer::GetAPI() ) {

            case RendererAPI::API::None: FGE_CORE_ASSERT( false, "RendererAPI::None is currently not supported!" ); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<GLShader>( filepath );

        }

        FGE_CORE_ASSERT( false, "No available API !" );

        return nullptr;

    }

	Ref<Shader> Shader::Create( const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc ) {

        switch( RendererAPI::GetAPI() ) {
            
            case RendererAPI::API::None: FGE_CORE_ASSERT( false, "RendererAPI::None is currently not supported!" ); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<GLShader>( name, vertexSrc, fragmentSrc );

        }

        FGE_CORE_ASSERT( false, "No available API !" );

        return nullptr;

    }

}
