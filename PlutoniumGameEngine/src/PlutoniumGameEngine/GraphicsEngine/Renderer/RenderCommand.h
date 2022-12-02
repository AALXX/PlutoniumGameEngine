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

		inline static void SetViewPort(uint32_t x, uint32_t  y, uint32_t width, uint32_t height) {
			s_RendererAPI->SetViewPort(x, y, width, height);
		}


		inline static void SetClearColor(const glm::vec4& color) {
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear(){
			s_RendererAPI->Clear();

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