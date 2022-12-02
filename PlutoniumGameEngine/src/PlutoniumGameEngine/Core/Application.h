#pragma once
#include "PlutoniumGameEngine/Core/Core.h"
#include "PlutoniumGameEngine/EventSystem/Event.h"
#include "PlutoniumGameEngine/EventSystem/AplicationEvent.h"
#include "PlutoniumGameEngine/Core/Window/Window.h"
#include "PlutoniumGameEngine/Core/LayerSystem/LayerStack.h"
#include "PlutoniumGameEngine/IamGui/IamGuiLayer.h"
#include "PlutoniumGameEngine/GraphicsEngine/Shaders/Shader.h"
#include "PlutoniumGameEngine/Core/Timestep/TimeStep.h"	

#include "PlutoniumGameEngine/GraphicsEngine/Buffer/Buffer.h"
#include "PlutoniumGameEngine/GraphicsEngine/Buffer/VertexArray.h"
#include "PlutoniumGameEngine/GraphicsEngine/Cameras/OrtographicCamera/OrthographicCamera.h"

#include <glm/glm.hpp>


namespace PGE {
	class Application
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
		bool OnWindowResize(WindowResizeEvent& e);
	private:

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;

		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	//*To be defined in client
	Application* CreateApplication();

}