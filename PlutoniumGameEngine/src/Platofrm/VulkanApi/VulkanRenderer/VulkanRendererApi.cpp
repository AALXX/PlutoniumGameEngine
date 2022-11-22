#include "pphd.h"
#include "VulkanRendererApi.h"
#include <Platofrm/VulkanApi/VulkanInstance/VulkanInstance.h>
#include <Platofrm/VulkanApi/Logging/Logging.h>
#include <Platofrm/VulkanApi/Device/Device.h>
#include <Platofrm/VulkanApi/Swapchain/Swapchain.h>




namespace PGE_VULKAN {

	bool VulkanRendererAPI::Init()
	{
		CreateVulkanInstance();
		CreateVulkanDevice();

		return true;
	}

	void VulkanRendererAPI::GetWindow(GLFWwindow* window, int windowWidth, int windowHeight)
	{
		m_windowHandle = window;
		m_windowHandleWidth = windowWidth;
		m_windowHandleHeight = windowHeight;

	}

	void VulkanRendererAPI::SetClearColor(const glm::vec4& color)
	{
	}

	void VulkanRendererAPI::Clear()
	{
	}

	void VulkanRendererAPI::DrawIndexed()
	{
		//drawFrame();

	}

	void VulkanRendererAPI::SubmitVertices(glm::mat3x3& Recivedvertices)
	{
	}

	void VulkanRendererAPI::WindowResized(int width, int height)
	{
	}


	bool VulkanRendererAPI::release(){

		device.waitIdle();


		for (SwapChainFrame frame : swapchainFrames) {
			device.destroyImageView(frame.imageView);
		}

		device.destroySwapchainKHR(swapChain);
		device.destroy();

		instance.destroySurfaceKHR(surface);

		if (isDebug) {
			instance.destroyDebugUtilsMessengerEXT(debugMessenger, nullptr, dldi);
		}

		instance.destroy();
		return true;
	}

	void VulkanRendererAPI::CreateVulkanInstance()
	{
		instance = make_instance(isDebug, "Plutonium engine");
		dldi = vk::DispatchLoaderDynamic(instance, vkGetInstanceProcAddr);

		if (isDebug) {
			debugMessenger = make_debug_messenger(instance, dldi);
		}

		VkSurfaceKHR c_stye_surface;

		if (glfwCreateWindowSurface(instance, m_windowHandle, nullptr, &c_stye_surface) != VK_SUCCESS) {
			if (isDebug) {
				PGE_CORE_ERROR("failed to abstact glfw surface for Vulkan \n");
			}
		}
		else if (isDebug) {
			PGE_CORE_ERROR("Sucessfully abstact glfw surface for Vulkan \n");

		}

		surface = c_stye_surface;
	}

	void VulkanRendererAPI::CreateVulkanDevice()
	{
		physicalDevice = choose_physical_device(instance, isDebug);
		device = create_logical_device(physicalDevice, surface,isDebug);
		std::array<vk::Queue, 2> queues = get_queues(physicalDevice, device, surface, isDebug);

		graphicsQueue = queues[0];
		presentQueue = queues[1];
		SwapChainBundle bundle = create_swapchain(device, physicalDevice, surface, m_windowHandleWidth, m_windowHandleHeight, isDebug);
		swapChain = bundle.swapchain;
		swapchainFrames = bundle.frames;
		swapChainFormat = bundle.format;
		swapChainExtent = bundle.extent;
	}

}
