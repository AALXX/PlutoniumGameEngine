#pragma once
#include "Core/Core.h"
#include "LogingSystem/Log.h"
#include"EventSystem/Event.h"
#include"EventSystem/AplicationEvent.h"
#include "LayerSystem/LayerStack.h"
#include "../PlutoniumGameEngine/GraphicsEngine/WindowSystem/Window.h"

//* Graphics engine
#include "GraphicsEngine/GraphicsEngine.h"

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
		void Stop();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverLay(Layer* layer);
	private:

		bool OnWindowClosed(WindowCloseEvent& e);

		bool m_running = true;
		
		//*Layer stack
		LayerStack m_layer_stack;

		//*Window
		std::unique_ptr<Window> m_Window;

		//*Window handler 
		HWND WindowHwnd;

		//*SwapChain
		SwapChain* m_swap_chain;
	};
	
	//*To be defined in client
	Aplication* CreateAplication();
}