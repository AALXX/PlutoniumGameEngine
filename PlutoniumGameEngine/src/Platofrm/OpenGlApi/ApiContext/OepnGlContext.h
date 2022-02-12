#pragma once
#include "PlutoniumGameEngine/GraphicsEngine/GraphicsContext/GraphicsContext.h"

struct GLFWwindow;

namespace PGE_OPENGL {
	class OpenGlContext: public PGE::GraphicsContext
	{
	public:
		OpenGlContext(GLFWwindow* windwoHandle);


		virtual void Init() override;
		virtual void SwapBuffers() override;

		~OpenGlContext();

	private:

		GLFWwindow* m_WindowHandle;

	};
}