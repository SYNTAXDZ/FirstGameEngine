#pragma once

#include "Window.hpp"
#include "LayerStack.hpp"
#include "TimeStep.hpp"

#include "FGE/Events/Event.hpp"
#include "FGE/Events/ApplicationEvent.hpp"

#include "FGE/ImGui/ImGuiLayer.hpp"

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

        inline static Application& Get() { return *s_Instance; }

    private:
        bool OnWindowClose( WindowCloseEvent& e );
        bool OnWindowResize( WindowResizeEvent& e );

    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        bool m_Minimized = false;
        LayerStack m_LayerStack;
        ImGuiLayer* m_ImGuiLayer;
        float m_LastFrameTime = 0.0f;

        static Application* s_Instance;

    };

    Application* CreateApplication();


}
