#pragma once

#include "precompiled.h"

#include "Base.hpp"

#include <GL/glew.h>

#include "FGE/Events/Event.hpp"

#include "FGE/Renderer/GraphicsContext.hpp"

struct GLFWwindow;

namespace FGE {

    struct WindowProps {

        std::string Title;
        uint32_t Width;
        uint32_t Height;

        WindowProps( std::string title = "FirstGameEngine", 
                     uint32_t width = 1280, uint32_t height = 720 ) 
                     : Title( title ), Width( width ), Height( height ) {}
        
    };    

    class Window {

    public:
        using EventCallbackFn = std::function<void( Event& )>;
        
        Window( const WindowProps& props );
        ~Window();

        void OnUpdate();

        uint32_t GetWidth() const { return m_Data.Width; }
        uint32_t GetHeight() const { return m_Data.Height; }

        void SetEventCallback( const EventCallbackFn& callbak ) { m_Data.EventCallback = callbak; }
        void SetVSync( bool enabled );
        //bool IsVSync();

        void* GetNativeWindow() { return m_Window; }

        static Window* Create( const WindowProps& props = WindowProps() );
    
    private:
        void Init( const WindowProps& props );
        void Shutdown();
    
    private:
        GLFWwindow* m_Window;
        Ref<GraphicsContext> m_Context;
        
        struct WindowData {

            std::string Title;
            uint32_t Width, Height;
            bool VSync;

            EventCallbackFn EventCallback;

        };

        WindowData m_Data;        

    };
    
}