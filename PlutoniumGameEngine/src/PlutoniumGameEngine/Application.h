#pragma once
#include "Core/Core.h"
#include"EventSystem/Event.h"
#include"EventSystem/AplicationEvent.h"
#include"PlutoniumGameEngine/Window/Window.h"

namespace PGE {
	class PGE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};
	
	//*To be defined in client
	Application* CreateApplication();
}