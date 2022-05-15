#include "pphd.h"
#include "OepnGlContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace PGE_OPENGL {

	OpenGlContext::OpenGlContext(GLFWwindow* windwoHandle)
		: m_WindowHandle(windwoHandle)
	{
		PGE_CORE_ASSERT(m_WindowHandle, "window handle is null");
	}

	void OpenGlContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PGE_CORE_ASSERT(status, "Failed to init GLAD");

		PGE_CORE_INFO("OpenGL Info:");
		PGE_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		PGE_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		PGE_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

		PGE_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Plutonium requires at least OpenGL version 4.5!");
	}

	void OpenGlContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

	OpenGlContext::~OpenGlContext()
	{
	}

}