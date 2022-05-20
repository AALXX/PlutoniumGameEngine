#include "pphd.h"

#include "Application.h"

#include "PlutoniumGameEngine/Input/Input.h"

#include "PlutoniumGameEngine/GraphicsEngine/GraphicsEngine.h"

namespace PGE {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		PGE_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		GraphicsEngine::get()->init();


		//m_ImGuiLayer = new ImGuiLayer;
		//PushOverLay(m_ImGuiLayer);


	}

	Application::~Application()
	{
	}

	void Application::Run()
	{

		while (m_Running) {
			//RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
			//RenderCommand::Clear();

			RenderCommand::DrawFrame();


			GraphicsEngine::get()->BeginScene();


			GraphicsEngine::get()->EndScene();


			for (Layer* layer : m_LayerStack){
				layer->OnUpdate();
			}

			//m_ImGuiLayer->Begin(); //begin imgui rendering

			//for (Layer* layer : m_LayerStack) {
			//	layer->OnImGuiRender();
			//}

			//m_ImGuiLayer->End(); //end imgui rendering


			m_Window->OnUpdate();
		}

	}
	
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dipathcer(e);
		dipathcer.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dipathcer.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled) {
				break;
			}
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverLay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);

	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		GraphicsEngine::get()->release();

		m_Running = false;
		return true;
	}

	bool  Application::OnWindowResize(WindowResizeEvent& e)
	{

		RenderCommand::WindowResized(e.GetWidth(), e.GetHeight());
		return false;
	}
}