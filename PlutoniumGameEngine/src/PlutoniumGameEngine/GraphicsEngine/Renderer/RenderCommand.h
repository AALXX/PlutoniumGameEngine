#pragma once

#include "RendererApi.h"

namespace PGE{

	class RenderCommand
	{
	public:

		inline static bool Init()
		{

			return s_RendererAPI->Init();
		}

		inline static void GetWindow(GLFWwindow* window, int windowWidth, int windowHeight) {
			s_RendererAPI->GetWindow(window, windowWidth, windowHeight);
		}

		inline static void SetClearColor(const glm::vec4& color) {
			s_RendererAPI->SetClearColor(color);
		}

		inline static void SubmitVertices(glm::mat3x3 &vertices) {
			s_RendererAPI->SubmitVertices(vertices);
		}

		inline static void Clear(){
			s_RendererAPI->Clear();

		}
		
		inline static void WindowResized(int width, int height) {
			s_RendererAPI->WindowResized(width, height);
		}

		inline static void DrawIndexed() {
			s_RendererAPI->DrawIndexed();
		}


		inline static bool release()
		{
			return s_RendererAPI->release();
		}


	private:

		static RendererAPI* s_RendererAPI;
	};

}