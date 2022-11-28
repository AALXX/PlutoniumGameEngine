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


		inline static void SetClearColor(const glm::vec4& color) {
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear(){
			s_RendererAPI->Clear();

		}
		
		inline static void WindowResized(int width, int height) {
			s_RendererAPI->WindowResized(width, height);
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexArray) {
			s_RendererAPI->DrawIndexed(vertexArray);
		}


		inline static bool release()
		{
			return s_RendererAPI->release();
		}


	private:

		static Renderer* s_RendererAPI;
	};

}