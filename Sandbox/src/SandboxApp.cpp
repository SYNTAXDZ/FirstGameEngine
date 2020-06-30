#include <Engine.hpp>

class Sandbox : public FGE::Application {

public:
    Sandbox() {}
    ~Sandbox() {}

};

FGE::Application* FGE::CreateApplication() {

    return new Sandbox();

}


