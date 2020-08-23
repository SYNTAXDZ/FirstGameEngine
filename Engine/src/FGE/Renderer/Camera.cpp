#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>


namespace FGE {

    Camera::Camera( float fov, float aspectRatio, float zNear, float zFar )
        : m_ProjectionMatrix( glm::perspective( glm::radians( fov ), aspectRatio, zNear, zFar ) ),
          m_ViewMatrix( glm::mat4( 1.0f ) ) {

        Yaw = -90.0f;
        Pitch = 0.0f;
        Sensetivity = 0.2f;
        WorldUp = Up;
        UpdateCameraVectors();

    }

    void Camera::SetProjectionMatrix( float fov, float aspectRatio, float zNear, float zFar ) {

        m_ProjectionMatrix = glm::perspective( glm::radians( fov ), aspectRatio, zNear, zFar );

    }

    void Camera::SetViewMatrix() {

        m_ViewMatrix = glm::lookAt( m_Position, m_Position + Front, Up );

    }

    void Camera::UpdateCameraVectors() {

        glm::vec3 front;
        front.x = glm::cos( glm::radians( Yaw ) ) * glm::cos( glm::radians( Pitch ) );
        front.y = glm::cos(glm::radians(Pitch));
        front.z = glm::sin( glm::radians( Yaw ) ) * glm::cos( glm::radians( Pitch ) );
        Front = glm::normalize( front );

        Right = glm::normalize( glm::cross( Front, WorldUp ) );

        Up = glm::normalize( glm::cross( Right, Front ) );

    }

} // namespace FGE
