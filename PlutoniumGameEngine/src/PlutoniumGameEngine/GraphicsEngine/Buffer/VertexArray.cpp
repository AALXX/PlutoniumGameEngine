#include "pphd.h"
#include "VertexArray.h"

#include "PlutoniumGameEngine/GraphicsEngine/Renderer/RendererApi.h"
#include "Platofrm/OpenGlApi/Buffer/OpenGlVerexArray.h"

namespace PGE {
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:    PGE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGl:  return new PGE_OPENGL::OpenGLVertexArray();
		}

		PGE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
