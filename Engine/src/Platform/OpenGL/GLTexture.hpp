#pragma once

#include "FGE/Renderer/Texture.hpp"

#include <GL/glew.h>

namespace FGE {

    class GLTexture2D : public Texture2D {

    public:
        GLTexture2D( uint32_t width, uint32_t height );
        GLTexture2D( const std::string& path );
        virtual ~GLTexture2D();
        virtual uint32_t GetWidth() const override { return m_Width; }
        virtual uint32_t GetHeight() const override { return m_Height; }
        virtual uint32_t GetRendererID() const override { return m_RendererID; }

        virtual void SetData( void *data, uint32_t size ) override;

        virtual void Bind( uint32_t slot = 0 ) const override;

        virtual bool operator==( const Texture& other ) const override {

            return m_RendererID == ( ( GLTexture2D& )other ).m_RendererID;

        }

    private:
        std::string m_Path;
        uint32_t m_RendererID;
        uint32_t m_Width, m_Height;
        GLenum m_InternalFormat, m_DataFormat;

    };

}