#include "pphd.h"
#include "VulkanRendererApi.h"

#include "Platofrm/VulkanApi/Instance/Instance.h"
#include "Platofrm/VulkanApi/Logging/Logging.h"
#include "Platofrm/VulkanApi/Suraface/Surface.h"
#include "Platofrm/VulkanApi/SwapChain/SwapChain.h"
#include "Platofrm/VulkanApi/Device/Device.h"


namespace PGE_VULKAN {

	bool VulkanRendererAPI::Init()
	{
		
		makeInstance();
		createSurface(m_windowHandle);
		makeDevice();
		createSwapChain();
		createImageViews();

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

	bool VulkanRendererAPI::release()
	{

		for (auto imageView : swapChainImageViews) {
			device.destroyImageView(imageView);
		}
		
		
		device.destroySwapchainKHR(swapChain);

		instance.destroySurfaceKHR(surface);


		device.destroy();

		instance.destroyDebugUtilsMessengerEXT(debugMessenger, nullptr, dldi);


		instance.destroy();
		return true;
	}

	void VulkanRendererAPI::makeInstance()
	{
		instance = make_instance(isDebug, "Plutonium engine");

		dldi = vk::DispatchLoaderDynamic(instance, vkGetInstanceProcAddr);

		if (isDebug) {
			debugMessenger = make_debug_messenger(instance, dldi);
		}
	}

	void VulkanRendererAPI::createSurface(GLFWwindow* windwoHandle)
	{

		surface = create_surface(instance, windwoHandle);
	}

	void VulkanRendererAPI::makeDevice()
	{
		//chose physical device
		physicalDevice = choose_phisical_device(instance, isDebug, surface);

		//create logical devices
		create_logical_device(physicalDevice, device, surface, isDebug, graphicsQueue, presentQueue);
	}

	void VulkanRendererAPI::createSwapChain()
	{
		create_swap_chain(physicalDevice, surface, m_windowHandleWidth, m_windowHandleHeight, isDebug, device, 
			swapChain, swapChainImages, swapChainImageFormat, swapChainExtent);
	}

	void VulkanRendererAPI::createImageViews()
	{
		create_image_views(swapChainImages, swapChainImageViews, swapChainImageFormat, device, isDebug);
	}

}
