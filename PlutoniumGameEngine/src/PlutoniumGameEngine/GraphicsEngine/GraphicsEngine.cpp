#include "pphd.h"
#include "GraphicsEngine.h"
#include <Platofrm/OpenGlApi/OpenGLShader/OpenGLShader.h>

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

	void GraphicsEngine::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4&transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<PGE_OPENGL::OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<PGE_OPENGL::OpenGLShader>(shader)->UploadUniformMat4("u_ModelMatrix", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}

	bool GraphicsEngine::release()
	{
		return RenderCommand::release();
	}


}
