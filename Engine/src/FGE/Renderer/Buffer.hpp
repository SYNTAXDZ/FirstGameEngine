#pragma once

#include "FGE/Core/Log.hpp"
#include "FGE/Core/Base.hpp"

namespace FGE {

    // We Define Some DataTypes for our Shader
    enum class ShaderDataType {

        None = 0, Float, Float2, Float3, Float4, Int, Int2, Int3, Int4,
        Mat3, Mat4, Bool

    };

    // This Helper Function Calculate The Size of the DataType
    static uint32_t ShaderDataTypeSize( ShaderDataType type ) {
		
        switch( type ) {

            case ShaderDataType::None: return 0;
			case ShaderDataType::Float:    return 4;
			case ShaderDataType::Float2:   return 4 * 2;
			case ShaderDataType::Float3:   return 4 * 3;
			case ShaderDataType::Float4:   return 4 * 4;
            // here for example a mat3 is 3 columns and rows of floats: float size is 4
            // we multiply by 3 for 3 columns and by 3 for 3 rows
			case ShaderDataType::Mat3:     return 4 * 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4 * 4;
			case ShaderDataType::Int:      return 4;
			case ShaderDataType::Int2:     return 4 * 2;
			case ShaderDataType::Int3:     return 4 * 3;
			case ShaderDataType::Int4:     return 4 * 4;
			case ShaderDataType::Bool:     return 1;
		
        }

		FGE_CORE_ASSERT( false, "Unknown ShaderDataType!" );
		
        return 0;
	}

    // BufferElement Representation
    struct BufferElement {

        // Name of The Element example: a_Position, a_Color
        std::string Name;
        // Type like Float2, Int3 ...
        ShaderDataType Type;
        // The Size of The Element
        uint32_t Size;
        // The Offset for each Element Inside The BufferLayout
        size_t Offset;
        // Is it Normalized
        bool Normalized;

        BufferElement() = default;
        // Here We Construct By The Type first, and The name as Second To Make The API Nice
        BufferElement( ShaderDataType type, const std::string& name, bool normalized = false )
			: Name( name ), Type( type ), Size( ShaderDataTypeSize( type ) ),
              Offset( 0 ), Normalized( normalized ) {}

		uint32_t GetComponentCount() const {
			
            switch( Type ) {

                case ShaderDataType::None:    return 0;
				case ShaderDataType::Float:   return 1;
				case ShaderDataType::Float2:  return 2;
				case ShaderDataType::Float3:  return 3;
				case ShaderDataType::Float4:  return 4;
				case ShaderDataType::Mat3:    return 3 * 3; // 3* float3
				case ShaderDataType::Mat4:    return 4 * 4; // 4* float4
				case ShaderDataType::Int:     return 1;
				case ShaderDataType::Int2:    return 2;
				case ShaderDataType::Int3:    return 3;
				case ShaderDataType::Int4:    return 4;
				case ShaderDataType::Bool:    return 1;
			
            }

			FGE_CORE_ASSERT( false, "Unknown ShaderDataType!" );
			
            return 0;
		
        }        

    };

    // BufferLayout Representation
    class BufferLayout {

    public:
        BufferLayout() {}
        // Initialize With The BufferElements like a_Position, a_TexCoord...
        // And We Converted The initializer_list to a vector
        BufferLayout( const std::initializer_list<BufferElement>& elements ) : m_Elements( elements ) {
            // Calculate The Stride and Offsets Between Vertices
            CalculateOffsetsAndStride();

        }

        uint32_t GetStride() const { return m_Stride; }
        std::vector<BufferElement> GetElements() const { return m_Elements; }


        std::vector<BufferElement>::iterator begin() { return m_Elements.begin();  }
        std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
        std::vector<BufferElement>::reverse_iterator rbegin() { return m_Elements.rbegin(); }
		std::vector<BufferElement>::reverse_iterator rend() { return m_Elements.rend(); }
        
        std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end()	const { return m_Elements.end(); }
		std::vector<BufferElement>::const_reverse_iterator rbegin() const { return m_Elements.rbegin(); }
		std::vector<BufferElement>::const_reverse_iterator rend() const { return m_Elements.rend(); }

    
    private:
        void CalculateOffsetsAndStride() {

            size_t offset = 0;
            m_Stride = 0;

            for( auto& element : m_Elements ) {
                
                // Here The Element.Offset is the Size of The previeus Element
                element.Offset = offset;
                offset += element.Size;
                m_Stride += element.Size;

            }

        }
    private:
        std::vector<BufferElement> m_Elements;
        uint32_t m_Stride = 0;

    };


    class VertexBuffer {

    public:
        virtual ~VertexBuffer() = default;

        virtual void Bind() const = 0;
        virtual void UnBind() const = 0;

        virtual void SetData( const void* data, uint32_t size ) const = 0;

        virtual const BufferLayout& GetLayout() const = 0;
        virtual void SetLayout( const BufferLayout& layout ) = 0;

        // static Ref<VertexBuffer> Create( uint32_t size ); 
        static Ref<VertexBuffer> Create( float* vertices, uint32_t size ); 

    };

    class IndexBuffer {
	
    public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static Ref<IndexBuffer> Create( uint32_t* indices, uint32_t count );
	
    };
    
} // namespace FGE
