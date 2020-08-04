#pragma once

#include "Window.hpp"
#include "LayerStack.hpp"

#include "FGE/Events/Event.hpp"
#include "FGE/Events/ApplicationEvent.hpp"

#include "FGE/ImGui/ImGuiLayer.hpp"

#include "FGE/Renderer/Buffer.hpp"

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

    private:
        std::unique_ptr<Window> m_Window;
        LayerStack m_LayerStack;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;

        unsigned int m_VAO, m_VBO, m_IBO;

        Ref<VertexBuffer> m_VertexBuffer;
        Ref<IndexBuffer> m_IndexBuffer;

        static Application* s_Instance;

    };

    Application* CreateApplication();


}