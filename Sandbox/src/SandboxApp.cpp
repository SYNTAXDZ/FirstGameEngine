#include <Engine.hpp>
#include "FGE/Core/EntryPoint.hpp"

#include "ExampleLayer.hpp"


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


