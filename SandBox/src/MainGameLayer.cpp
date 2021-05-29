#include "MainGameLayer.h"

MainGameLayer::MainGameLayer() : Layer("GameLayer")
{
}

MainGameLayer::~MainGameLayer()
{
}

void MainGameLayer::OnAttach()
{
	PGE_CLIENT_INFO("AAAAA");
}

void MainGameLayer::OnDeAttach()
{
}

void MainGameLayer::OnUpdate()
{
	//PGE_CLIENT_INFO("test");

}

void MainGameLayer::OnEvent(PGE::Event& event)
{
}
