#pragma once

#include "PlutoniumGameEngine/IamGui/IamGuiApiRenderer.h"

namespace PGE_OPENGL {
	class IamGuiOpenGlRenderer: public PGE::IAmGuiRendererAPI {
	public:
		virtual void Begin() override;
		virtual void End() override;

		virtual void OnAttach() override;
		virtual void OnDettach() override;
		virtual void OnImGuiRender() override;
	};
}