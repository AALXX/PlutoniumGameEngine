#pragma once

#include "PlutoniumGameEngine/Core/LayerSystem/Layer.h"

#include "PlutoniumGameEngine/EventSystem/AplicationEvent.h"
#include "PlutoniumGameEngine/EventSystem/KeyEvent.h"
#include "PlutoniumGameEngine/EventSystem/MouseEvent.h"
#include "PlutoniumGameEngine/IamGui/IamGuiApiRenderer.h"

namespace PGE {

	class ImGuiLayer : public Layer
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
		IAmGuiRendererAPI* m_iamgui_renderer;

		float m_Time = 0.0f;
	};

}