#include "CameraController.hpp"

#include "KeyCodes.hpp"
#include "MouseCodes.hpp"
#include "Input.hpp"
#include "Base.hpp"

namespace FGE {

    inline static bool firstMouse = true;
    inline static float lastX = 400.0f;
    inline static float lastY = 300.0f;

    CameraController::CameraController( float aspectRatio )
        : m_AspectRatio( aspectRatio ), m_Camera( m_ZoomLevel, m_AspectRatio, 0.1f, 100.0f ) {}


    void CameraController::OnUpdate( Timestep ts ) {

        float translationSpeed =  m_CameraTranslationSpeed * ts.GetSeconds();

        if( Input::IsKeyPressed( KeyCode::A ) )
            m_CameraPosition -= m_Camera.Right * translationSpeed; 
        else if( Input::IsKeyPressed( KeyCode::D ) )
            m_CameraPosition += m_Camera.Right * translationSpeed;
        else if( Input::IsKeyPressed( KeyCode::W ) )
            m_CameraPosition += m_Camera.Front * translationSpeed;
        else if( Input::IsKeyPressed( KeyCode::S ) )
            m_CameraPosition -= m_Camera.Front * translationSpeed;

        m_Camera.SetPosition( m_CameraPosition );

    }

    void CameraController::OnEvent( Event &e ) {

        EventDispatcher dispatcher( e );
        dispatcher.Dispatch<MouseMovedEvent>( BIND_FN( CameraController::OnMouseMoved ) );
        dispatcher.Dispatch<MouseScrolledEvent>( BIND_FN( CameraController::OnMouseScrolled ) );
        dispatcher.Dispatch<WindowResizeEvent>(BIND_FN(CameraController::OnWindowResize ) );

    }

    void CameraController::ProcessMouseMovement( float offsetX, float offsetY, bool constrainPitch ) {

        offsetX *= m_Camera.Sensetivity;
        offsetY *= m_Camera.Sensetivity;

        m_Camera.Yaw += offsetX;
        m_Camera.Pitch += offsetY;

        if( constrainPitch ) {

            if( m_Camera.Pitch > 90.0f )
                m_Camera.Pitch = 90.0f;
            if( m_Camera.Pitch < -90.0f )
                m_Camera.Pitch = -90.0f;

        }

        m_Camera.UpdateCameraVectors();

    }

    bool CameraController::OnMouseMoved( MouseMovedEvent& e ) {

        if( firstMouse ) {

            lastX = e.GetX();
            lastY = e.GetY();

            firstMouse = false;

        }

        float offsetX = e.GetX() - lastX;
        float offsetY = lastY - e.GetY();

        lastX = e.GetX();
        lastY = e.GetY();

        ProcessMouseMovement( offsetX, offsetY );

        return false;

    }

    bool CameraController::OnMouseScrolled( MouseScrolledEvent &e ) {

        if( m_ZoomLevel >= 1.0f && m_ZoomLevel <= 45.0f )
            m_ZoomLevel -= e.GetYOffset();
        if( m_ZoomLevel <= 1.0f )
            m_ZoomLevel = 1.0f;
        if( m_ZoomLevel >= 45.0f )
            m_ZoomLevel -= e.GetYOffset();

        m_Camera.SetProjectionMatrix( m_ZoomLevel, m_AspectRatio, 0.1f, 100.0f );

        return false;

    }

    bool CameraController::OnWindowResize( WindowResizeEvent &e ) {

        m_AspectRatio = ( float )( e.GetWidth() )/( float )( e.GetHeight() );
        m_Camera.SetProjectionMatrix( m_ZoomLevel, m_AspectRatio, 0.1f, 100.0f );

        return false;

    }

}
