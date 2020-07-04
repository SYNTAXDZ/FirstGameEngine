#pragma once

#include "../Events/ApplicationEvent.hpp"
#include "../Events/MouseEvent.hpp"
#include "../Events/KeyEvent.hpp"

namespace FGE {
    class Application {

    public:
        Application();
        // we use virtual distructor because this class will be inherited by
        // The SandboxApp
        virtual ~Application();

        void Run();

    };

    Application* CreateApplication();


}