#include "pphd.h"
#include "VulkanRendererApi.h"

#include "Platofrm/VulkanApi/Instance/Instance.h"
#include "Platofrm/VulkanApi/Logging/Logging.h"
#include "Platofrm/VulkanApi/Device/Device.h"
#include "Platofrm/VulkanApi/Suraface/Surface.h"


namespace PGE_VULKAN {

	bool VulkanRendererAPI::Init()
	{
		
		makeInstance();
		createSurface(m_windowHandle);
		makeDevice();


		return true;
	}

	void VulkanRendererAPI::GetWindow(GLFWwindow* window)
	{
		m_windowHandle = window;
	}

	void VulkanRendererAPI::SetClearColor(const glm::vec4& color)
	{
	}

	void VulkanRendererAPI::Clear()
	{
	}

	bool VulkanRendererAPI::release()
	{

		instance.destroyDebugUtilsMessengerEXT(debugMessenger, nullptr, dldi);
		
		instance.destroySurfaceKHR(surface);

		device.destroy();

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
		physicalDevice = choose_phisical_device(instance, isDebug);

		//create logical devices
		create_logical_device(physicalDevice, device, surface, isDebug, graphicsQueue, presentQueue);
	}

}
