#pragma once
#include "PlutoniumGameEngine/Core/LogingSystem/Log.h"
#include "PlutoniumGameEngine/Core/Application.h"

//* application entry point
#ifdef PGE_PLATFORM_WINDOWS

extern PGE::Application* PGE::CreateApplication();

int main(int argc, char** argv) {
	PGE::Log::Init();

	auto app = PGE::CreateApplication();
	app->Run();
	delete app;
}

#endif // PGE_PLATFORM_WINDOWS
