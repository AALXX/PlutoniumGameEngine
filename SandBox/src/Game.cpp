#include <PlutoniumGameEngine.h>
#include <iostream>

class GameLayer : public PGE::Layer
{
public:
	GameLayer()
		: Layer("Game")
	{
	}

	void OnUpdate() override
	{
		PGE_CLIENT_TRACE("GameLayer: update");
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