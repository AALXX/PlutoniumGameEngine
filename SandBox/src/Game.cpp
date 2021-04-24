#include <PlutoniumGameEngine.h>
#include <iostream>

class GameLayer : public PGE::Layer
{
public:
	GameLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		std::cout << "Example layer:Update \n";
	}


	void OnEvent(PGE::Event& event) override
	{

	}

};

class Game : public PGE::Aplication
{
public:
	Game() {
		PushLayer(new GameLayer());
	}
	~Game() {}

};

PGE::Aplication* PGE::CreateAplication() {

	return new Game;
}