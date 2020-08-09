#include <Engine.hpp>
#include <imgui/imgui.h>

class ExampleLayer : public FGE::Layer {

    public:
        ExampleLayer() : Layer( "ExampleLayer" ) {}

        virtual void OnUpdate() override {

            if( FGE::Input::IsKeyPressed( FGE_KEY_SPACE ) )
                FGE_INFO( "Key Pressed" );

            //FGE_INFO( "ExampleLayer::OnUpdate" );

        }

        virtual void OnImGuiRender() override {

            ImGui::Begin( "Window" );
            ImGui::Text( "This is a Text" );
            ImGui::End();

        }

        virtual void OnEvent( FGE::Event& event ) override {

            //FGE_TRACE( "{0}", event );

        }

};

class Sandbox : public FGE::Application {

public:
    Sandbox() {
        // Push The Layer To The Stack of Layers
        PushLayer( new ExampleLayer() );

    }
    ~Sandbox() {}

};

FGE::Application* FGE::CreateApplication() {

    return new Sandbox();

}


