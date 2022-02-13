#include "pphd.h"
#include "OpenGLRendererApi.h"

#include <glad/glad.h>

namespace PGE_OPENGL {
	bool OpenGLRendererAPI::Init()
	{
		return true;
	}
	void OpenGLRendererAPI::GetWindow(GLFWwindow* window)
	{
	}
	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}
	
	void OpenGLRendererAPI::DrawIndexed()
	{
		PGE_CORE_INFO("impllement gl draw elements");
	}
	bool OpenGLRendererAPI::release()
	{
		return true;
	}
}
