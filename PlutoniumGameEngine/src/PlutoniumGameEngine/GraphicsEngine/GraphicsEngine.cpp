#include "pphd.h"
#include "GraphicsEngine.h"

namespace PGE {

	GraphicsEngine::SceneData* GraphicsEngine::m_SceneData = new GraphicsEngine::SceneData;

	bool GraphicsEngine::init()
	{

		return RenderCommand::Init();
	}


	void GraphicsEngine::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void GraphicsEngine::EndScene()
	{
	}

	void GraphicsEngine::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UploadUnifromMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	bool GraphicsEngine::release()
	{
		return RenderCommand::release();
	}


}
