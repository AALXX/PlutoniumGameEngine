#pragma once
#include "../LogingSystem/Log.h"
#include "../Application.h"

//* application entry point
#ifdef PGE_PLATFORM_WINDOWS

extern PGE::Application* PGE::CreateApplication();

int main(int argc, char** argv) {
	PGE::Log::Init();
	PGE_CORE_WARN("Initialized Log!");

	auto app = PGE::CreateApplication();
	app->Run();
	delete app;
}

#endif // PGE_PLATFORM_WINDOWS
