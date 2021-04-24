#pragma once
#include "Core/Core.h"
#include"EventSystem/Event.h"
#include "LayerSystem/LayerStack.h"

namespace PGE {
	class PGE_API Aplication
	{
	public:
		Aplication();
		virtual ~Aplication();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverLay(Layer* layer);
	private:
		LayerStack m_layer_stack;
	};
	
	//*To be defined in client
	Aplication* CreateAplication();
}