#include <PlutoniumGameEngine.h>


class TestLayer:public PGE::Layer
{
public:
	TestLayer() :Layer("Example") {

	}

	void OnUpdate() override {
		PGE_CLIENT_INFO("Example Layer Updafe");
	}

	void OnEvent(PGE::Event& event) override {
		PGE_CLIENT_TRACE("{0}", event);
	}

private:

};

class Sandbox : public PGE::Application
{
public:
	Sandbox()
	{
		PushLayer(new TestLayer());
	}

	~Sandbox()
	{

	}

};

PGE::Application* PGE::CreateApplication()
{
	return new Sandbox();
}