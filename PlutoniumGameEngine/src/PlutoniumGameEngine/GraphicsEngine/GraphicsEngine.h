#pragma once

#include "Renderer/RenderCommand.h"

namespace PGE {


	class GraphicsEngine
	{

	public:
		GraphicsEngine();

		// initialize engine
		bool init();

		void BeginScene();
		void EndScene();
		
		//TODO IMPLEMENT VERTEX ARRAy
		void Submit();


		bool release();

		~GraphicsEngine();

	public:
		static GraphicsEngine* get();	

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); };

	};
}

