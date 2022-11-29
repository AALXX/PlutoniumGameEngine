#include "pphd.h"
#include "Texture.h"

#include "PlutoniumGameEngine/GraphicsEngine/Renderer/RendererApi.h"
#include "Platofrm/OpenGlApi/Texture/OpenGLTexture.h"

namespace PGE {
    Ref<Texture2D> PGE::Texture2D::Create(const std::string& path)
    {
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:    PGE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGl:  return std::make_shared<PGE_OPENGL::OpenGLTexture2D>(path);
		}

		PGE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
    }
}