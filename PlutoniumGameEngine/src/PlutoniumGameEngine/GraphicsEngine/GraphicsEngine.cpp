#include "pphd.h"
#include "GraphicsEngine.h"
#include "Platofrm/VulkanApi/Instance/Instance.h"
#include "Platofrm/VulkanApi/Logging/Logging.h"
#include "Platofrm/VulkanApi/Device/Device.h"

namespace PGE {

	GraphicsEngine::GraphicsEngine()
	{
	}

	bool GraphicsEngine::init()
	{
		makeInstance();

		makeDevice();

		return true;
	}

	bool GraphicsEngine::release()
	{

		instance.destroyDebugUtilsMessengerEXT(debugMessenger, nullptr, dldi);

		instance.destroy();
		return true;
	}

	GraphicsEngine::~GraphicsEngine()
	{
	}

	GraphicsEngine* GraphicsEngine::get()
	{
		static GraphicsEngine engine;
		return &engine;
	}

	void GraphicsEngine::makeInstance()
	{
		instance = PGE_VULKAN::make_instance(isDebug, "Plutonium engine");

		dldi = vk::DispatchLoaderDynamic(instance, vkGetInstanceProcAddr);

		if (isDebug) {
			debugMessenger = PGE_VULKAN::make_debug_messenger(instance, dldi);
		}
	}

	void GraphicsEngine::makeDevice()
	{
		physicalDevice = PGE_VULKAN::choose_phisical_device(instance, isDebug);
	}

}
