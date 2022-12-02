#pragma once
#include "PlutoniumGameEngine/Core/Core.h"
#include "PlutoniumGameEngine/EventSystem/Event.h"
#include "PlutoniumGameEngine/Core/Timestep/TimeStep.h"

namespace PGE {
	
	class PGE_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDeAttach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}