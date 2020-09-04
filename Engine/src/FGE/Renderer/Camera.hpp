#pragma once

#include <glm/glm.hpp>

namespace FGE {

    class Camera {

    public:
        Camera( float fov, float aspectRatio, float zNear, float zFar );

        void SetPosition( const glm::vec3& position ) { m_Position = position; SetViewMatrix();  }
        const glm::vec3& GetPosition() { return m_Position; }

        void SetProjectionMatrix( float fov, float aspectRatio, float zNear, float zFar );
        glm::mat4 GetProjectionMatrix() { return m_ProjectionMatrix; }

        void SetViewMatrix();
        glm::mat4 GetViewMatrix() { return m_ViewMatrix; }

        void UpdateCameraVectors();
    public:
        float Yaw, Pitch, Sensetivity;
        glm::vec3 Front = glm::vec3( 0.0f, 0.0f, 1.0f );
        glm::vec3 Right = glm::vec3( 1.0f, 0.0f, 0.0f );
        glm::vec3 Up = glm::vec3( 0.0f, 1.0f, 0.0f );
        glm::vec3 WorldUp;

    private:
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;

        glm::vec3 m_Position = glm::vec3( 0.0f, 0.0f, 3.0f );

    };

}
