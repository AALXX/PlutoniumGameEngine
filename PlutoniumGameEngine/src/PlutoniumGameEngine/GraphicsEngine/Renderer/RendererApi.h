#pragma once
  
#include <glm/glm.hpp>
#include <PlutoniumGameEngine/GraphicsEngine/Buffer/VertexArray.h>

namespace PGE {
	
	enum class RendererAPI {
		None = 0, Vulkan = 1, OpenGl = 2
	};

	class Renderer
	{

	public:

		virtual bool Init() = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		
		virtual void SetViewPort(uint32_t x, uint32_t  y, uint32_t width, uint32_t height) = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		virtual bool release() = 0;

		inline static RendererAPI GetAPI() { return s_RendererAPI; };

	private:
		static RendererAPI s_RendererAPI;
	};

}

