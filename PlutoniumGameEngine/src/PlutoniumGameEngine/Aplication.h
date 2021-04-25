#pragma once
#include "Core/Core.h"
#include "LogingSystem/Log.h"
#include"EventSystem/Event.h"
#include "LayerSystem/LayerStack.h"
#include "../PlutoniumGameEngine/GraphicsEngine/WindowSystem/Window.h"

namespace PGE {
	class PGE_API Aplication
	{
	public:
		Aplication();
		virtual ~Aplication();

		void Run() {
			Start();
			Update();
		}
		
		void Start();
		void Update();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverLay(Layer* layer);
	private:

		bool OnWindowClosed(WindowCloseEvent& e);

		bool m_running = true;
		LayerStack m_layer_stack;
		std::unique_ptr<Window> m_Window;
	};
	
	//*To be defined in client
	Aplication* CreateAplication();
}