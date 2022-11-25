#include "pphd.h"
#include "OpenGLRendererApi.h"

#include <glad/glad.h>
#include "..\IamGuiOpenGl\IamGuiOpengl.h"
#include <iostream>

namespace PGE_OPENGL {
	bool OpenGLRendererAPI::Init()
	{

		return true;
	}
	void OpenGLRendererAPI::GetWindow(GLFWwindow* window, int windowWidth, int windowHeight)
	{
	}
	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
	}

	void OpenGLRendererAPI::Clear()
	{

	}
	
	void OpenGLRendererAPI::DrawIndexed()
	{

	}

	void OpenGLRendererAPI::SubmitVertices(glm::mat3x3 &vertices)
	{

	}

	bool OpenGLRendererAPI::release()
	{
		return true;
	}
}
