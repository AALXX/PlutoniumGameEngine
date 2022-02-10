#include <PlutoniumGameEngine.h>

#include "imgui/imgui.h"

class TestLayer:public PGE::Layer
{
public:
	TestLayer() :Layer("Example") {

	}

	void OnUpdate() override {
		//PGE_CLIENT_INFO("Example Layer Update");
	}

	void OnEvent(PGE::Event& event) override {
		if (event.GetEventType() == PGE::EventType::KeyPressed)
		{
			PGE::KeyPressedEvent& e = (PGE::KeyPressedEvent&)event;
			if (e.GetKeyCode() == PGE_KEY_TAB)
				PGE_CORE_TRACE("Tab key is pressed (event)!");
			PGE_CORE_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("CUM");
		ImGui::Text("TEST");
		ImGui::End();
	}
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