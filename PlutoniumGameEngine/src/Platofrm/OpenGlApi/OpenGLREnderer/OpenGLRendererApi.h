#pragma once

#include "PlutoniumGameEngine/GraphicsEngine/Renderer/RendererApi.h"

namespace PGE_OPENGL {
	class OpenGLRendererAPI : public PGE::RendererAPI {
	public:

		virtual bool Init() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed() override;
		virtual bool release() override;
	};
}