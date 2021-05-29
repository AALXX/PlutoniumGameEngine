#include "Aplication.h"
#include <iostream>

namespace PGE {

#define BIND_EVENT_FUNC(x) std::bind(&Aplication::x, this, std::placeholders::_1)

	Aplication::Aplication()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNC(OnEvent));
	}

	Aplication::~Aplication()
	{
	}

	void Aplication::PushLayer(Layer* layer)
	{
		//*TOD REPAIR LAYERSISTYEM
		m_layer_stack.PushLayer(layer);
	}

	void Aplication::PushOverLay(Layer* layer)
	{
		m_layer_stack.PushOverlay(layer);
	}

	//* aplictaion lifetime
	void Aplication::Start()
	{
		Log::Init();
		PGE_CORE_INFO("Started Engine");

		GraphicsEngine::get()->Init();
		m_swap_chain =  GraphicsEngine::get()->createSwapChain();

		WindowHwnd =  m_Window->GetHwnd();


		RECT rc = m_Window->getClientWindowRect();
		m_swap_chain->Init(WindowHwnd, rc.right - rc.left, rc.bottom - rc.top);
	}

	void Aplication::Update()
	{
		while (m_running) {

			GraphicsEngine::get()->getImmediateDeviceContext()->ClearRenderTargetColor(this->m_swap_chain, 1, 1,0, 1);
			m_swap_chain->present(false);

			for (Layer* layer : m_layer_stack)
			{
				layer->OnUpdate();
			}

			m_Window->OnUpdate();

		};
	}

	void Aplication::Stop()
	{
		m_swap_chain->Release();
		GraphicsEngine::get()->Release();

	}


	//* Events
	bool Aplication::OnWindowClosed(WindowCloseEvent& e)
	{

		Stop();

		m_running = false;
		return true;
	}

	void Aplication::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(OnWindowClosed));


		for (auto it = m_layer_stack.end(); it != m_layer_stack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}


	Aplication* CreateAplication()
	{
		return nullptr;
	}
}