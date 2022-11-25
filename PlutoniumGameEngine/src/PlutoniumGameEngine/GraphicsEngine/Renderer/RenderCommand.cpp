#include "pphd.h"
#include "RenderCommand.h"

#include "Platofrm/VulkanApi/VulkanRenderer/VulkanRendererApi.h"
#include "Platofrm/OpenGlApi/OpenGLREnderer/OpenGLRendererApi.h"

namespace PGE {

	Renderer * RenderCommand::s_RendererAPI = new PGE_OPENGL::OpenGLRendererAPI;

	//Renderer* RenderCommand::s_RendererAPI = new PGE_VULKAN::VulkanRendererAPI;
}