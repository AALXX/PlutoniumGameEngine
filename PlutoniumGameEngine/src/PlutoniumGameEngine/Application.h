#pragma once
#include "Core/Core.h"
#include "EventSystem/Event.h"
#include "EventSystem/AplicationEvent.h"
#include "PlutoniumGameEngine/Window/Window.h"
#include "PlutoniumGameEngine/LayerSystem/LayerStack.h"
#include "PlutoniumGameEngine/IamGui/IamGuiLayer.h"
#include "PlutoniumGameEngine/GraphicsEngine/Shaders/Shader.h"
#include "PlutoniumGameEngine/Core/Timestep/TimeStep.h"	

#include <glm/glm.hpp>
#include <PlutoniumGameEngine/GraphicsEngine/Buffer/Buffer.h>
#include <PlutoniumGameEngine/GraphicsEngine/Buffer/VertexArray.h>
#include <PlutoniumGameEngine/GraphicsEngine/Cameras/OrtographicCamera/OrthographicCamera.h>

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

		LayerStack m_LayerStack;

		float m_LastFrameTime = 0.0f;

	private:
		static Application* s_Instance;
	};

	//*To be defined in client
	Application* CreateApplication();

}