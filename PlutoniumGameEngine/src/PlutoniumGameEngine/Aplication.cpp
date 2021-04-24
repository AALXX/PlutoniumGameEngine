#include "Aplication.h"
#include"EventSystem/AplicationEvent.h"


namespace PGE {
	Aplication::Aplication()
	{
	}

	Aplication::~Aplication()
	{
	}

	void Aplication::PushLayer(Layer* layer)
	{
		m_layer_stack.PushLayer(layer);
	}

	void Aplication::PushOverLay(Layer* layer)
	{
		m_layer_stack.PushOverlay(layer);
	}

	void Aplication::Run()
	{
		
		WindowResizeEvent e(800, 800);

		while (true) {
			for (Layer* layer : m_layer_stack)
			{
				layer->OnUpdate();
			}
		};
	}

	void Aplication::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		//dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

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