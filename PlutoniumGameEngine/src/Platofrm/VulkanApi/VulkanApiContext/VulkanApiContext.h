#pragma once
#include "PlutoniumGameEngine/GraphicsEngine/GraphicsContext/GraphicsContext.h"

struct GLFWwindow;

namespace PGE_VULKAN {
	class VulkanContext : public PGE::GraphicsContext
	{
	public:
		VulkanContext(GLFWwindow* windwoHandle);


		virtual void Init() override;
		virtual void SwapBuffers() override;

		~VulkanContext();

	private:

		GLFWwindow* m_WindowHandle;

	};
}