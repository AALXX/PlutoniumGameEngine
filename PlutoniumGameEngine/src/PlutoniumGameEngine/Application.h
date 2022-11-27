#pragma once
#include "Core/Core.h"
#include "EventSystem/Event.h"
#include "EventSystem/AplicationEvent.h"
#include "PlutoniumGameEngine/Window/Window.h"
#include "PlutoniumGameEngine/LayerSystem/LayerStack.h"
#include "PlutoniumGameEngine/IamGui/IamGuiLayer.h"
#include "PlutoniumGameEngine/GraphicsEngine/Shaders/Shader.h"

#include <glm/glm.hpp>
#include <PlutoniumGameEngine/GraphicsEngine/Buffer/Buffer.h>
#include <PlutoniumGameEngine/GraphicsEngine/Buffer/VertexArray.h>

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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;

		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;
	private:
		static Application* s_Instance;

	private:

		glm::mat3x3 m_vertices = {
			-0.5f, -0.5f, 0.0f,
			0.5f,  -0.5f, 0.0f,
			0.0f,   0.5f, 0.0f,
		};
	};

	//*To be defined in client
	Application* CreateApplication();

}