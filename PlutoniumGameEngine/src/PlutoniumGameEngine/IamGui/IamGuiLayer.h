#pragma 
#include "PlutoniumGameEngine/LayerSystem/Layer.h"
#include "PlutoniumGameEngine/EventSystem/Event.h"
#include "PlutoniumGameEngine/EventSystem/MouseEvent.h"
#include "PlutoniumGameEngine/EventSystem/KeyEvent.h"
#include "PlutoniumGameEngine/EventSystem/AplicationEvent.h"
#include "PlutoniumGameEngine/Core/Core.h"

namespace PGE {
	class PGE_API IamGuiLayer: public Layer
	{
	public:
		IamGuiLayer();
		~IamGuiLayer();

		void OnUpdate();
		void OnEvent(Event& event);

		void OnAttach();
		void OnDeAttach();
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMoveReleasedEvent(MouseMovedEvent& e);
		bool OnMouseScrollReleasedEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);

		bool OnKeyTypedEvent(KeyTypedEvent& e);

		bool OnWindowResizeEvent(WindowResizeEvent& e);

	private:
		float m_Time = 0.0f;
	};

}