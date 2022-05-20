#include "pphd.h"
#include "RenderCommand.h"

#include "Platofrm/VulkanApi/VulkanRenderer/VulkanRendererApi.h"
#include "Platofrm/OpenGlApi/OpenGLREnderer/OpenGLRendererApi.h"

namespace PGE {

	//RendererAPI * RenderCommand::s_RendererAPI = new PGE_OPENGL::OpenGLRendererAPI;

	RendererAPI* RenderCommand::s_RendererAPI = new PGE_VULKAN::VulkanRendererAPI;
}