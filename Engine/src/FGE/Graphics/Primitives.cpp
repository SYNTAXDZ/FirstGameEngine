#include "Primitives.hpp"
#include "FGE/Renderer/Renderer.hpp"
#include <GL/glew.h>

using namespace FGE;

Sphere::Sphere( const Ref<Shader>& shader, const glm::mat4& pos ) : m_Shader( shader ), m_Position( pos ) {

    SetData();
    m_VertexArray = FGE::VertexArray::Create();

    //m_Shader = FGE::Shader::Create(
    //  "/home/syntax/Base/Knowledge/learn_cpp/CppProjects/FirstGameEngine/"
     // "Sandbox/assets/shaders/PBR.glsl");
    m_VertexBuffer = FGE::VertexBuffer::Create(m_Data.data(), m_Data.size());

    FGE::BufferLayout layout = {

      {FGE::ShaderDataType::Float3, "a_Position"},
      {FGE::ShaderDataType::Float2, "a_TexCoord"},
      {FGE::ShaderDataType::Float3, "a_Normal"},

    };
    m_VertexBuffer->SetLayout(layout);

    // 12/ 4 = 3 (count of indicies)
    //m_IndexBuffer = FGE::IndexBuffer::Create( m_Indices.data(), m_Indices.size() / sizeof( uint32_t ) );
    m_IndexBuffer = FGE::IndexBuffer::Create( m_Indices.data(), m_Indices.size() );

    m_VertexArray->AddVertexBuffer(m_VertexBuffer);
    m_VertexArray->SetIndexBuffer(m_IndexBuffer);

}

Sphere::~Sphere() {}

Ref<Sphere> Sphere::Create( const Ref<Shader>& shader, const glm::mat4& pos ) {

    return CreateRef<Sphere>( shader, pos );

}

void Sphere::SetData() {

    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> uv;
    std::vector<glm::vec3> normals;

    const unsigned int X_SEGMENTS = 64;
    const unsigned int Y_SEGMENTS = 64;
    const float PI = 3.14159265359;


    for( unsigned int y = 0; y <= Y_SEGMENTS; ++y ) {

        for( unsigned int x = 0; x <= X_SEGMENTS; ++x ) {

            float xSegment = (float)x / (float)X_SEGMENTS;
            float ySegment = (float)y / (float)Y_SEGMENTS;
            float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            float yPos = std::cos(ySegment * PI);
            float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

            positions.push_back(glm::vec3(xPos, yPos, zPos));
            uv.push_back(glm::vec2(xSegment, ySegment));
            normals.push_back(glm::vec3(xPos, yPos, zPos));

        }

    }

    bool oddRow = false;
    for( unsigned int y = 0; y < Y_SEGMENTS; ++y ) {

        if( !oddRow ) {

            for( unsigned int x = 0; x <= X_SEGMENTS; ++x ) {

                m_Indices.push_back(y       * (X_SEGMENTS + 1) + x);
                m_Indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);

            }

        } else {

            for( int x = X_SEGMENTS; x >= 0; --x ) {

                m_Indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                m_Indices.push_back(y       * (X_SEGMENTS + 1) + x);

            }

        }

        oddRow = !oddRow;

    }

    for( unsigned int i = 0; i < positions.size(); ++i ) {

        m_Data.push_back(positions[i].x);
        m_Data.push_back(positions[i].y);
        m_Data.push_back(positions[i].z);

        if( uv.size() > 0 ) {

            m_Data.push_back(uv[i].x);
            m_Data.push_back(uv[i].y);

        }
        if( normals.size() > 0 ) {

            m_Data.push_back(normals[i].x);
            m_Data.push_back(normals[i].y);
            m_Data.push_back(normals[i].z);

        }

    }

}

void Sphere::Draw() {

    //SetData();
    Renderer::Submit( m_VertexArray, m_Shader, m_Position );

}

// renders (and builds at first invocation) a sphere
void Sphere::render() {

    if( sphereVAO == 0 ) {

        glGenVertexArrays(1, &sphereVAO);

        unsigned int vbo, ebo;
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        std::vector<glm::vec3> positions;
        std::vector<glm::vec2> uv;
        std::vector<glm::vec3> normals;
        std::vector<unsigned int> indices;

        const unsigned int X_SEGMENTS = 64;
        const unsigned int Y_SEGMENTS = 64;
        const float PI = 3.14159265359;
        for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
        {
            for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
            {
                float xSegment = (float)x / (float)X_SEGMENTS;
                float ySegment = (float)y / (float)Y_SEGMENTS;
                float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
                float yPos = std::cos(ySegment * PI);
                float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

                positions.push_back(glm::vec3(xPos, yPos, zPos));
                uv.push_back(glm::vec2(xSegment, ySegment));
                normals.push_back(glm::vec3(xPos, yPos, zPos));
            }
        }

        bool oddRow = false;
        for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
        {
            if (!oddRow) // even rows: y == 0, y == 2; and so on
            {
                for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
                {
                    indices.push_back(y       * (X_SEGMENTS + 1) + x);
                    indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                }
            }
            else
            {
                for (int x = X_SEGMENTS; x >= 0; --x)
                {
                    indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                    indices.push_back(y       * (X_SEGMENTS + 1) + x);
                }
            }
            oddRow = !oddRow;
        }
        indexCount = indices.size();

        std::vector<float> data;
        for (unsigned int i = 0; i < positions.size(); ++i)
        {
            data.push_back(positions[i].x);
            data.push_back(positions[i].y);
            data.push_back(positions[i].z);
            if (uv.size() > 0)
            {
                data.push_back(uv[i].x);
                data.push_back(uv[i].y);
            }
            if (normals.size() > 0)
            {
                data.push_back(normals[i].x);
                data.push_back(normals[i].y);
                data.push_back(normals[i].z);
            }
        }
        glBindVertexArray(sphereVAO);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
        float stride = (3 + 2 + 3) * sizeof(float);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(5 * sizeof(float)));
    }

    glBindVertexArray(sphereVAO);
    glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
}
