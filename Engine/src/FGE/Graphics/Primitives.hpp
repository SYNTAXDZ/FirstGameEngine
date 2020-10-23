#pragma once

#include "FGE/Renderer/Buffer.hpp"
#include "FGE/Renderer/VertexArray.hpp"
#include "FGE/Renderer/Shader.hpp"
#include <glm/glm.hpp>

namespace FGE {

    class Sphere {

    public:
        Sphere( const Ref<Shader>& shader, const glm::mat4& pos );
        ~Sphere();

	static Ref<Sphere> Create( const Ref<Shader>& shader, const glm::mat4& pos );
        void Draw();
        Ref<VertexArray>& GetVertexArray() { return m_VertexArray; }
        void SetData();
        void render();

    private:
        Ref<VertexArray> m_VertexArray;
        Ref<VertexBuffer> m_VertexBuffer;
        Ref<IndexBuffer> m_IndexBuffer;
        Ref<Shader> m_Shader;
        std::vector<float> m_Data;
        std::vector<uint32_t> m_Indices;

        unsigned int sphereVAO = 0;
        unsigned int indexCount = 0;

        glm::mat4 m_Position;
    };

}
