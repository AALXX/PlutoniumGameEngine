#pragma once
#ifdef PGE_PLATFORM_WINDOWS

extern PGE::Aplication* PGE::CreateAplication();

int main(int argc, char** argv) {

	auto app = PGE::CreateAplication();

	app->Run();
	delete app;
}

#endif // PGE_PLATFORM_WINDOWS
