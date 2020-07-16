#include "Input.hpp"
#include "Application.hpp"
#include <GLFW/glfw3.h>

namespace FGE {

    bool Input::IsKeyPressed( KeyCode key ) {

        auto window = static_cast<GLFWwindow*>( Application::Get().GetWindow().GetNativeWindow() );
        // get The Key
        auto state = glfwGetKey( window, static_cast<uint32_t>( key ) );
        // IF THE state is GLFW_PRESS or REPEAT so return true
        return state == GLFW_PRESS || state == GLFW_REPEAT;

    }

    bool Input::IsMouseButtonPresssed( MouseCode button ) {
        // Get The Window from the Application
        auto window = static_cast<GLFWwindow*>( Application::Get().GetWindow().GetNativeWindow() );
        auto state = glfwGetMouseButton( window, static_cast<uint32_t>( button ) );

        return state == GLFW_PRESS;

    }

    std::pair<float, float> Input::GetMousePosition() {

        auto window = static_cast<GLFWwindow*>( Application::Get().GetWindow().GetNativeWindow() );
        double xpos, ypos;

        glfwGetCursorPos( window, &xpos, &ypos );

        return { ( float )xpos, ( float )ypos };

    }

    float Input::GetMouseX() {

        auto [x, y] = GetMousePosition();

        return x;

    }

    float Input::GetMouseY() {

        auto [x, y] = GetMousePosition();

        return y;

    }
    
} // namespace FGE
