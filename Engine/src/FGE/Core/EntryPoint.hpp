#pragma once

extern FGE::Application* FGE::CreateApplication();

int main( int argc, char** argv ) {

    auto app = FGE::CreateApplication();
    app->Run();

    delete app;

}
