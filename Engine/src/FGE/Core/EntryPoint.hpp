#pragma once

extern FGE::Application* FGE::CreateApplication();

int main( int argc, char** argv ) {

    FGE::Log::Init();
    FGE_CORE_INFO( "Engine Started !!" );

    auto app = FGE::CreateApplication();
    FGE_INFO( "Ready !!" );
    app->Run();

    delete app;

}
