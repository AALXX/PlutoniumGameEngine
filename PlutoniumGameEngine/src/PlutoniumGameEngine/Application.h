#pragma once
#include "Core/Core.h"
#include"EventSystem/Event.h"
#include"EventSystem/AplicationEvent.h"
#include"PlutoniumGameEngine/Window/Window.h"
#include"PlutoniumGameEngine/LayerSystem/LayerStack.h"

namespace PGE {
	class PGE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		//Event Handler
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverLay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
	};
	
	//*To be defined in client
	Application* CreateApplication();
}