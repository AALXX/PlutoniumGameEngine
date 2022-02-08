#pragma once

#include "PlutoniumGameEngine/LayerSystem/Layer.h"

#include "PlutoniumGameEngine/EventSystem/AplicationEvent.h"
#include "PlutoniumGameEngine/EventSystem/KeyEvent.h"
#include "PlutoniumGameEngine/EventSystem/MouseEvent.h"

namespace PGE {

	class PGE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDeAttach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}