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

		makeDevice();

		return true;
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

	void VulkanRendererAPI::createSurface()
	{

	}

	void VulkanRendererAPI::makeDevice()
	{
		//chose physical device
		physicalDevice = choose_phisical_device(instance, isDebug);

		//create logical devices
		graphicsQueue = create_logical_device(physicalDevice, device, isDebug);
	}
}
