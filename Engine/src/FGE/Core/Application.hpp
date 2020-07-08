#pragma once

#include "Window.hpp"

#include "FGE/Events/Event.hpp"
#include "FGE/Events/ApplicationEvent.hpp"


namespace FGE {
    class Application {

    public:
        Application();
        // we use virtual distructor because this class will be inherited by
        // The SandboxApp
        virtual ~Application();

        void Run();

        void OnEvent( Event& e );

    private:
        bool OnWindowClose( WindowCloseEvent& e );

    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;

    };

    Application* CreateApplication();


}