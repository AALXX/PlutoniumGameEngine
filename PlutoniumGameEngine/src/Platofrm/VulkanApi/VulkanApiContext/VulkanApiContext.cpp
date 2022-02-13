#include "pphd.h"
#include "VulkanApiContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Platofrm/VulkanApi/VulkanRenderer/VulkanRendererApi.h"
#include "PlutoniumGameEngine/GraphicsEngine/Renderer/RenderCommand.h"


namespace PGE_VULKAN {

	VulkanContext::VulkanContext(GLFWwindow* windwoHandle)
		: m_WindowHandle(windwoHandle)
	{

		PGE_CORE_ASSERT(m_WindowHandle, "window handle is null");
		
		PGE::RenderCommand::GetWindow(windwoHandle);
	}

	void VulkanContext::Init()
	{
	}

	void VulkanContext::SwapBuffers()
	{

	}

	VulkanContext::~VulkanContext()
	{
	}

}