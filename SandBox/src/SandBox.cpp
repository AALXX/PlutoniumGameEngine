#include <PlutoniumGameEngine.h>

class Sandbox : public PGE::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}

};

PGE::Application* PGE::CreateApplication()
{
	return new Sandbox();
}