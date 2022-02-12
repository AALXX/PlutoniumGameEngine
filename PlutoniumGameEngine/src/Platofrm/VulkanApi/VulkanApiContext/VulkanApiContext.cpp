#include "pphd.h"
#include "VulkanApiContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace PGE_VULKAN {

	VulkanContext::VulkanContext(GLFWwindow* windwoHandle)
		: m_WindowHandle(windwoHandle)
	{
		PGE_CORE_ASSERT(m_WindowHandle, "window handle is null");
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