#pragma once 

#include "FGE/Core/Layer.hpp"
#include "FGE/Events/Event.hpp"

namespace FGE {

    class ImGuiLayer : public Layer {

    public:
        ImGuiLayer();
        ~ImGuiLayer() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();

        void BlockEvents( bool block ) { m_BlockEvents = block; }
    
    private:
        bool m_BlockEvents = true;
        float m_Time = 0.0f;

    };

}