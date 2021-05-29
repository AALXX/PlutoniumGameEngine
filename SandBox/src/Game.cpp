#include <PlutoniumGameEngine.h>

//* -------------Entrypoint-----------
#include "PlutoniumGameEngine/EntryPoint/EntryPoint.h"
//* ----------------------------------

#include "MainGameLayer.h"
#include <iostream>

class ExampleLayer : public PGE::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnAttach()
	{
		PGE_CLIENT_INFO("AAAAA");
	}


	void OnUpdate() override
	{
		//PGE_CLIENT_INFO("ExampleLayer::Update");
	}

	void OnEvent(PGE::Event& event) override
	{

	}

};


class Game : public PGE::Aplication
{
public:
	Game() {
		PushLayer(new ExampleLayer());
	}
	~Game() {}

};

PGE::Aplication* PGE::CreateAplication() {

	return new Game;
}