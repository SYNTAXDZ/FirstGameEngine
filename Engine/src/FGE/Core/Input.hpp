#pragma once

#include "FGE/Core/Base.hpp"
#include "FGE/Core/KeyCodes.hpp"
#include "FGE/Core/MouseCodes.hpp"

namespace FGE {

    class Input {

    public:
        static bool IsKeyPressed( KeyCode code );

        static bool IsMouseButtonPresssed( MouseCode button );
        static std::pair<float, float> GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();

    };

} // namespace FGE 