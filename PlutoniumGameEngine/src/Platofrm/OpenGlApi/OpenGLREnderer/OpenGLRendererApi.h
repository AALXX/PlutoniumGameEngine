#pragma once

#include "PlutoniumGameEngine/GraphicsEngine/Renderer/RendererApi.h"
#include <Platofrm/OpenGlApi/Buffer/OpenGlBuffer.h>
#include <PlutoniumGameEngine/GraphicsEngine/Buffer/VertexArray.h>

namespace PGE_OPENGL {
	class OpenGLRendererAPI : public PGE::Renderer {
	public:

		virtual bool Init() override;

		virtual void SetViewPort(uint32_t x, uint32_t  y, uint32_t width, uint32_t height) override;


		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed(const PGE::Ref<PGE::VertexArray>& vertexArray) override;

		virtual void WindowResized(int width, int height) {
			PGE_CORE_TRACE("{0}, {1}", width, height);
		};
		virtual bool release() override;
	};
}