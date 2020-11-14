#include "PBRLayer.hpp"
#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GL/glew.h>

uint32_t sphereVAO = 0;
uint32_t indexCount = 0;
// renders (and builds at first invocation) a sphere
// void renderSphere() {

//     if( sphereVAO == 0 ) {

//         glGenVertexArrays(1, &sphereVAO);

//         unsigned int vbo, ebo;
//         glGenBuffers(1, &vbo);
//         glGenBuffers(1, &ebo);

//         std::vector<glm::vec3> positions;
//         std::vector<glm::vec2> uv;
//         std::vector<glm::vec3> normals;
//         std::vector<unsigned int> indices;

//         const unsigned int X_SEGMENTS = 64;
//         const unsigned int Y_SEGMENTS = 64;
//         const float PI = 3.14159265359;
//         for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
//         {
//             for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
//             {
//                 float xSegment = (float)x / (float)X_SEGMENTS;
//                 float ySegment = (float)y / (float)Y_SEGMENTS;
//                 float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
//                 float yPos = std::cos(ySegment * PI);
//                 float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

//                 positions.push_back(glm::vec3(xPos, yPos, zPos));
//                 uv.push_back(glm::vec2(xSegment, ySegment));
//                 normals.push_back(glm::vec3(xPos, yPos, zPos));
//             }
//         }

//         bool oddRow = false;
//         for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
//         {
//             if (!oddRow) // even rows: y == 0, y == 2; and so on
//             {
//                 for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
//                 {
//                     indices.push_back(y       * (X_SEGMENTS + 1) + x);
//                     indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
//                 }
//             }
//             else
//             {
//                 for (int x = X_SEGMENTS; x >= 0; --x)
//                 {
//                     indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
//                     indices.push_back(y       * (X_SEGMENTS + 1) + x);
//                 }
//             }
//             oddRow = !oddRow;
//         }
//         indexCount = indices.size();

//         std::vector<float> data;
//         for (unsigned int i = 0; i < positions.size(); ++i)
//         {
//             data.push_back(positions[i].x);
//             data.push_back(positions[i].y);
//             data.push_back(positions[i].z);
//             if (uv.size() > 0)
//             {
//                 data.push_back(uv[i].x);
//                 data.push_back(uv[i].y);
//             }
//             if (normals.size() > 0)
//             {
//                 data.push_back(normals[i].x);
//                 data.push_back(normals[i].y);
//                 data.push_back(normals[i].z);
//             }
//         }
//         glBindVertexArray(sphereVAO);
//         glBindBuffer(GL_ARRAY_BUFFER, vbo);
//         glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
//         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
//         glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
//         float stride = (3 + 2 + 3) * sizeof(float);
//         glEnableVertexAttribArray(0);
//         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
//         glEnableVertexAttribArray(1);
//         glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
//         glEnableVertexAttribArray(2);
//         glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, stride, (void*)(5 * sizeof(float)));
//     }

//     glBindVertexArray(sphereVAO);
//     glDrawElements(GL_TRIANGLE_STRIP, indexCount, GL_UNSIGNED_INT, 0);
// }

PBRLayer::PBRLayer() : Layer( "PBRLayer" ), m_CameraController( 800.0f / 600.0f ) {

    m_PBRShader = FGE::Shader::Create(
        "/home/syntax/Base/Knowledge/learn_cpp/FirstGameEngine/"
        "Sandbox/assets/shaders/PBR.glsl");

    // lights
    // ------
    m_LightPositions = {
        glm::vec3(-10.0f, 10.0f, 10.0f),
        glm::vec3(10.0f, 10.0f, 10.0f),
        glm::vec3(-10.0f, -10.0f, 10.0f),
        glm::vec3(10.0f, -10.0f, 10.0f),
    };
    m_LightColors = {
        glm::vec3(300.0f, 300.0f, 300.0f), glm::vec3(300.0f, 300.0f, 300.0f),
        glm::vec3(300.0f, 300.0f, 300.0f), glm::vec3(300.0f, 300.0f, 300.0f)
    };

    int nrRows = 7;
    int nrColumns = 7;
    float spacing = 2.5;

    m_VertexArray = FGE::VertexArray::Create();

}

void PBRLayer::OnAttach() {

    float cube_vertices[] = {
        // Front face
        -1.0, -1.0, 1.0, 0.0f, 0.0f, 1.0f,  0.0f,  0.0f,
        1.0, -1.0, 1.0, 0.0f, 0.0f, 1.0f,   1.0f,  0.0f,
        1.0, 1.0, 1.0, 0.0f, 0.0f, 1.0f,    1.0f,  1.0f,
        -1.0, 1.0, 1.0, 0.0f, 0.0f, 1.0f,   0.0f,  1.0f,
        // Back face
        -1.0, -1.0, -1.0, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -1.0, 1.0, -1.0, 0.0f, 0.0f, -1.0f,  0.0f, 1.0f,
        1.0, 1.0, -1.0, 0.0f, 0.0f, -1.0f,   1.0f, 1.0f,
        1.0, -1.0, -1.0, 0.0f, 0.0f, -1.0f,  1.0f, 0.0f,

        // Top face
        -1.0, 1.0, -1.0, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -1.0, 1.0, 1.0, 0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        1.0, 1.0, 1.0, 0.0f, 1.0f, 0.0f,   1.0f, 1.0f,
        1.0, 1.0, -1.0, 0.0f, 1.0f, 0.0f,  1.0f, 1.0f,

        // Bottom face
        -1.0, -1.0, -1.0, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        1.0, -1.0, -1.0, 0.0f, -1.0f, 0.0f,  1.0f, 0.0f,
        1.0, -1.0, 1.0, 0.0f, -1.0f, 0.0f,   1.0f, 0.0f,
        -1.0, -1.0, 1.0, 0.0f, -1.0f, 0.0f,  0.0f, 0.0f,

        // Right face
        1.0, -1.0, -1.0, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        1.0, 1.0, -1.0, 1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        1.0, 1.0, 1.0, 1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
        1.0, -1.0, 1.0, 1.0f, 0.0f, 0.0f,  1.0f, 0.0f,

        // Left face
        -1.0, -1.0, -1.0, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -1.0, -1.0, 1.0, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -1.0, 1.0, 1.0, -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        -1.0, 1.0, -1.0, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,

    };

    uint32_t cubeIndices[] = {
        0,  1,  2,  0,  2,  3,  // front
        4,  5,  6,  4,  6,  7,  // back
        8,  9,  10, 8,  10, 11, // top
        12, 13, 14, 12, 14, 15, // bottom
        16, 17, 18, 16, 18, 19, // right
        20, 21, 22, 20, 22, 23, // left
    };
    m_VertexBuffer = FGE::VertexBuffer::Create( cube_vertices, sizeof( cube_vertices ) );

    FGE::BufferLayout layout = {

        {FGE::ShaderDataType::Float3, "a_Position"},
        {FGE::ShaderDataType::Float3, "a_Normal"},
        {FGE::ShaderDataType::Float2, "a_TexCoords"},

    };
    m_VertexBuffer->SetLayout(layout);

    // 12/ 4 = 3 (count of indicies)
    m_IndexBuffer = FGE::IndexBuffer::Create( cubeIndices, sizeof( cubeIndices ) / sizeof( uint32_t ) );

    m_VertexArray->AddVertexBuffer( m_VertexBuffer );
    m_VertexArray->SetIndexBuffer( m_IndexBuffer );


    m_PBRShader->Bind();
    m_PBRShader->SetFloat3( "u_Albedo", glm::vec3( 0.8f, 0.1f, 0.0f ) );
    m_PBRShader->SetFloat( "u_Mettalic", 0.8f );
    m_PBRShader->SetFloat( "u_Roughness", 0.1f );
    m_PBRShader->SetFloat( "u_AO", 1.0f );


    glm::mat4 model = glm::mat4( 1.0f );
    model = glm::translate( model, glm::vec3( 0.0f, 0.0f, -5.0f ) );
    m_Sphere = FGE::Sphere::Create( m_PBRShader, model );

}

void PBRLayer::OnUpdate( FGE::Timestep ts ) {

    m_CameraController.OnUpdate( ts );

    FGE::RenderCommand::Clear();
    FGE::RenderCommand::SetClearColor( glm::vec4( 0.2f, 0.1f, 0.1f, 1.0f ) );

    FGE::Renderer::BeginScene( m_CameraController.GetCamera() );
       glm::mat4 model = glm::mat4( 1.0f );
       model = glm::translate( model, glm::vec3( 0.0f, 0.0f, -5.0f ) );

       m_PBRShader->SetFloat3("u_CamPos", m_CameraController.GetCamera().GetPosition());
       FGE::Renderer::Submit( m_VertexArray, m_PBRShader, model );
       //m_Sphere->Draw();
       //FGE::Renderer::EndScene();

   //FGE::Renderer::BeginScene( m_CameraController.GetCamera() );

   // render light source (simply re-render sphere at light positions)
   // this looks a bit off as we use the same shader, but it'll make their
   // positions obvious and keeps the codeprint small.
   /*for (unsigned int i = 0; i < m_LightPositions.size() / sizeof( m_LightPositions[0] ); ++i) {

       m_PBRShader->Bind();

       glm::vec3 newPos = m_LightPositions[i];

       m_PBRShader->SetFloat3("lightPositions[" + std::to_string(i) + "]",
                            newPos);

       m_PBRShader->SetFloat3("lightColors[" + std::to_string(i) + "]",
                            m_LightColors[i]);

       model = glm::mat4( 1.0f );
       model = glm::translate( model, newPos );
       model = glm::scale( model, glm::vec3( 0.5f ) );
       FGE::Renderer::Submit( m_VertexArray, m_PBRShader, model );

   }
   */
   FGE::Renderer::EndScene();

}

void PBRLayer::OnImGuiRender() {

    ImGui::Begin( "Window" );
    ImGui::Text( "This is a Text" );
    ImGui::End();

}

void PBRLayer::OnEvent( FGE::Event& event ) {

    m_CameraController.OnEvent( event );

}
