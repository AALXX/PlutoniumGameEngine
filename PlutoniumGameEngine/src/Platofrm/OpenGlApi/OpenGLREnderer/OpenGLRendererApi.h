#pragma once

#include "PlutoniumGameEngine/GraphicsEngine/Renderer/RendererApi.h"

namespace PGE_OPENGL {
	class OpenGLRendererAPI : public PGE::RendererAPI {
	public:

		virtual bool Init() override;
		virtual void GetWindow(GLFWwindow* window, int width, int height) override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed() override;
		virtual void DrawFrame() {};
		virtual void WindowResized(int width, int height) {
			PGE_CORE_TRACE("{0}, {1}", width, height);
		};
		virtual bool release() override;
	};
}