#include "GLTexture.hpp"
#include "GLDebug.hpp"
#include "FGE/Core/Log.hpp"

#include <stb_image/stb_image.h>

namespace FGE {

    GLTexture2D::GLTexture2D( uint32_t width, uint32_t height ) : m_Width( width ), m_Height( height ) {

        m_InternalFormat = GL_RGBA8;
        m_DataFormat = GL_RGBA;

        glCreateTextures( GL_TEXTURE_2D, 1, &m_RendererID );
        glTextureStorage2D( m_RendererID, 1, m_InternalFormat, m_Width, m_Height );

        glTextureParameteri( m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTextureParameteri( m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

        glTextureParameteri( m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTextureParameteri( m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT );

    }

    /*
    GLTexture2D::GLTexture2D( const std::string& path ) : m_Path( path ) {

        int width, height, channels;
        stbi_set_flip_vertically_on_load( 1 );
        stbi_uc *data = nullptr;

        data = stbi_load( path.c_str(), &width, &height, &channels, 0 );
        FGE_CORE_ASSERT( data, "Failed to load image!" );

        m_Width = width;
        m_Height = height;

        GLenum internalFormat = 0, dataFormat = 0;
        if( channels == 4 ) {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;

        } else if( channels == 3 ) {

            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;

        } else if( channels == 1 ) {

            internalFormat = GL_RED;
            dataFormat = GL_RED;

        }

        m_InternalFormat = internalFormat;
        m_DataFormat = dataFormat;

        FGE_CORE_ASSERT( internalFormat & dataFormat, "Format not supported!" );

        glCreateTextures( GL_TEXTURE_2D, 1, &m_RendererID );
        glTextureStorage2D( m_RendererID, 1, m_InternalFormat, m_Width, m_Height );

        glTextureParameteri( m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTextureParameteri( m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

        glTextureParameteri( m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTextureParameteri( m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT );

        glTextureSubImage2D( m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data );

        stbi_image_free( data );

    }
    */

// utility function for loading a 2D texture from file
// ---------------------------------------------------
    GLTexture2D::GLTexture2D( const std::string& path)
{
    
    glGenTextures(1, &m_RendererID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);

    GLenum format;
    if (data)
    {
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, m_RendererID);
        glCheckError();
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data); 
        glCheckError();
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        FGE_CORE_ERROR( "Texture failed to load at path: " );
        stbi_image_free(data);
    }

 
}

    GLTexture2D::~GLTexture2D() {

        glDeleteTextures(1, &m_RendererID );

    }

    void GLTexture2D::SetData( void *data, uint32_t size ) {

        uint32_t bpp = m_DataFormat == GL_RGBA? 4 : 3;
        glTextureSubImage2D( m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data );

    }

    void GLTexture2D::Bind( uint32_t slot ) const {

        // glActiveTexture( slot );
        glBindTextureUnit( slot, m_RendererID );
        glCheckError();

    }

}
