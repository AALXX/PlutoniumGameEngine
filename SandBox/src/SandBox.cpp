#include <PlutoniumGameEngine.h>


class TestLayer:public PGE::Layer
{
public:
	TestLayer() :Layer("Example") {

	}

	void OnUpdate() override {
		//PGE_CLIENT_INFO("Example Layer Update");
	}

	void OnEvent(PGE::Event& event) override {
		//PGE_CLIENT_TRACE("{0}", event);
	}

private:

};

class Sandbox : public PGE::Application
{
public:
	Sandbox()
	{
		PushLayer(new TestLayer());
		PushOverLay(new PGE::IamGuiLayer());
	}

	~Sandbox()
	{

	}

};

PGE::Application* PGE::CreateApplication()
{
	return new Sandbox();
}