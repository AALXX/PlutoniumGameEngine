#include <PlutoniumGameEngine.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
	glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
	View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
	View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
	return Projection * View * Model;
}


class TestLayer:public PGE::Layer
{
public:
	TestLayer() :Layer("Example") {

	}

	void OnUpdate() override {
		//PGE_CLIENT_INFO("Example Layer Update");
		if (PGE::Input::IsKeyPressed(PGE_KEY_A)) {
			PGE_CLIENT_INFO("MILSUGIOOO");
		}
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