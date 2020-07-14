#include <Engine.hpp>

class ExampleLayer : public FGE::Layer {

    public:
        ExampleLayer() : Layer( "ExampleLayer" ) {}

        virtual void OnUpdate() override {

            FGE_INFO( "ExampleLayer::OnUpdate" );

        }

        virtual void OnEvent( FGE::Event& event ) override {

            FGE_TRACE( "{0}", event );

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


