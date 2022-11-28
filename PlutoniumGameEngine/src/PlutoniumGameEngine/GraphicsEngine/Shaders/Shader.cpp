#include "pphd.h"
#include "Shader.h"


#include "PlutoniumGameEngine/GraphicsEngine/Renderer/RendererApi.h"
#include "Platofrm/OpenGlApi/OpenGLShader/OpenGLShader.h"

namespace PGE {
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:    PGE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGl:  return new PGE_OPENGL::OpenGLShader(vertexSrc, fragmentSrc);
		}

		PGE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
