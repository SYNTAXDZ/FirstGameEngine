#pragma once

#include "FGE/Core/TimeStep.hpp"

#include "FGE/Renderer/Camera.hpp"

#include "FGE/Events/Event.hpp"
#include "FGE/Events/MouseEvent.hpp"
#include "FGE/Events/ApplicationEvent.hpp"

namespace FGE {

    class CameraController {

    public:
        CameraController( float aspectRatio );

        void OnUpdate( Timestep ts );
        void OnEvent( Event& e );

        Camera& GetCamera() { return m_Camera; }
        void SetZoomLevel( float zoomLevel ) { m_ZoomLevel = zoomLevel; }
        float GetZoomLevel() { return m_ZoomLevel; }

    private:
        void ProcessMouseMovement( float offsetX, float offsetY, bool constrainPitch = true );
        bool OnMouseMoved( MouseMovedEvent& e );
        bool OnMouseScrolled( MouseScrolledEvent& e );
        bool OnWindowResize( WindowResizeEvent& e );

    private:
        float m_AspectRatio;
        float m_ZoomLevel = 45.0f;
        float m_CameraTranslationSpeed = 5.0f;
        Camera m_Camera;
        glm::vec3 m_CameraPosition = glm::vec3( 0.0f, 0.0f, 3.0f );

    };

}
