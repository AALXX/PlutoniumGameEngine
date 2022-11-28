#pragma once

#include "Renderer/RenderCommand.h"
#include <PlutoniumGameEngine/GraphicsEngine/Cameras/OrtographicCamera/OrtographicCamera.h>
#include <PlutoniumGameEngine/GraphicsEngine/Shaders/Shader.h>

namespace PGE {


	class GraphicsEngine
	{

	public:

		// initialize engine
		static bool init();

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();
		
		static void Submit( const Ref<Shader>& shader,const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));


		static bool release();


	public:
		inline static RendererAPI GetRenderAPI() { return Renderer::GetAPI(); };
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;

	};
}

