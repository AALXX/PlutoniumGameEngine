#pragma once
  
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace PGE {


	class RendererAPI
	{
	public:
		enum class API {
			None = 0, Vulkan = 1, OpenGl = 2
		};

	public:

		virtual bool Init() = 0;

		virtual void GetWindow(GLFWwindow* window, int windowWidth, int windowHeight) = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed() = 0;

		virtual bool release() = 0;

		inline static API GetAPI() { return s_RendererAPI; };

	private:
		static API s_RendererAPI;
	};

}

