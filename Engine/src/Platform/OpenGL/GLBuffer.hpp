#pragma once

#include "FGE/Renderer/Buffer.hpp"

namespace FGE {

    class GLVertexBuffer : public VertexBuffer {

    public:
        //GLVertexBuffer( uint32_t size );
        GLVertexBuffer( float* vertices, uint32_t size );
        virtual ~GLVertexBuffer();

        virtual void Bind() const override;
        virtual void UnBind() const override;

        virtual void SetData( const void* data, uint32_t size ) const override {}

        virtual const BufferLayout& GetLayout() const override {}
        virtual void SetLayout( const BufferLayout& layout ) override {}

    private:
        uint32_t m_RendererID;

    };

    class GLIndexBuffer : public IndexBuffer {
	
    public:
        GLIndexBuffer( uint32_t* indices, uint32_t count );
		virtual ~GLIndexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual uint32_t GetCount() const override { return m_Count; }

    private:
        uint32_t m_RendererID;
        uint32_t m_Count;
	
    };
    
} // namespace FGE
