#pragma once
#include "PlutoniumGameEngine.h"


class MainGameLayer : public PGE::Layer
{
public:
	MainGameLayer();
	virtual ~MainGameLayer();


	virtual void OnAttach() override;
	virtual void OnDeAttach() override;
	void OnUpdate() override;

	void OnEvent(PGE::Event& event) override;

};