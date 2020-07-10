#pragma once

#include "Window.hpp"
#include "LayerStack.hpp"

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

        void PushLayer( Layer* layer );
        void PushOverlay( Layer* overlay );

        Window& GetWindow() { return *m_Window; }

    private:
        bool OnWindowClose( WindowCloseEvent& e );

    private:
        std::unique_ptr<Window> m_Window;
        LayerStack m_LayerStack;
        bool m_Running = true;

    };

    Application* CreateApplication();


}