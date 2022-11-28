#include "pphd.h"
#include "OpenGLRendererApi.h"
#include <GLFW/glfw3.h>

#include <glad/glad.h>

namespace PGE_OPENGL {
	bool OpenGLRendererAPI::Init()
	{

		return true;
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::DrawIndexed(const PGE::Ref<PGE::VertexArray>& vertexArray)
	{
		//opengl draw call
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
	

	bool OpenGLRendererAPI::release()
	{
		return true;
	}
}
