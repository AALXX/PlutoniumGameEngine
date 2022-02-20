#pragma once
#include "pphd.h"
#include <vulkan/vulkan.hpp>

#include "Platofrm/VulkanApi/SwapChain/SwapChain.h"

#include "Platofrm/VulkanApi/Device/QueueIndices.h"

namespace PGE_VULKAN {

	const std::vector<const char*> requestedExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	//Physical devices
	void log_device_properties(const vk::PhysicalDevice& device) {

		//get device properties
		vk::PhysicalDeviceProperties properties = device.getProperties();

		PGE_CORE_INFO("Device name: {0}, device type:", properties.deviceName);

		switch (properties.deviceType)
		{
		case (vk::PhysicalDeviceType::eCpu):
			PGE_CORE_INFO("CPU");
			break;
		case (vk::PhysicalDeviceType::eDiscreteGpu):
			PGE_CORE_INFO("Discrete GPU");
			break;
		case (vk::PhysicalDeviceType::eIntegratedGpu):
			PGE_CORE_INFO("Integrated GPU");
			break;
		case (vk::PhysicalDeviceType::eVirtualGpu):
			PGE_CORE_INFO("Virtual GPU");
			break;
		default:
			PGE_CORE_INFO("Other");
		}

	}

	bool checkDeviceExtensionSupported(const vk::PhysicalDevice& device, const std::vector<const char*>& requestedExtensions, const bool& debug) {
		//check if a provided physical device can support a list of required extensions

		std::set<std::string>requiredExtensions(requestedExtensions.begin(), requestedExtensions.end());

		if (debug) {
			PGE_CORE_INFO("Device can support the folowing extensions: ");
		}

		for (vk::ExtensionProperties& extension : device.enumerateDeviceExtensionProperties()) {
			if (debug) {
				PGE_CORE_INFO("{0}", extension.extensionName);
			}

			//remove this from list of required extensions
			requiredExtensions.erase(extension.extensionName);
		}

		return requiredExtensions.empty();

	}

	bool isSuitable(const vk::PhysicalDevice& device, const bool debug, const vk::SurfaceKHR& surface) {
		if (debug) {
			PGE_CLIENT_TRACE("Checking if device is sutable");
		}


		if (debug) {
			PGE_CORE_INFO("We are requesting device extensions: {");

			for (const char* extension : requestedExtensions) {
				PGE_CORE_INFO("{0}", extension);
			}
			PGE_CORE_INFO("}");
		}

		if (bool extensionSupported = checkDeviceExtensionSupported(device, requestedExtensions, debug)) {
			if (debug) {
				PGE_CORE_INFO("Device can support the requested extensions");
			}
			else {
				if (debug) {
					PGE_CORE_INFO("Device can not support the requested extensions");
				}
				return false;
			}
		}

		bool swapChainAdequate = false;

		SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device, surface);
		swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();

		return true;
	}

	vk::PhysicalDevice choose_phisical_device(vk::Instance& instance, bool debug, const vk::SurfaceKHR surface) {
		/*chose a suitable physical device from list provided by host system*/
		if (debug)
		{
			PGE_CLIENT_TRACE("Choosing physical device");
		}


		//create a vector of physical devices
		std::vector<vk::PhysicalDevice> availableDevices = instance.enumeratePhysicalDevices();

		if (debug) {
			PGE_CORE_INFO("There are {0} physical devices available on this system", availableDevices.size());
		}

		//check if a suitable device can be found
		for (vk::PhysicalDevice device : availableDevices)
		{
			if (debug) {
				log_device_properties(device);
			}
			if (isSuitable(device, debug, surface)) {
				return device;
			}
		}

		return nullptr;

	}

	//Logical Devices
	bool supported(std::vector<const char*>& layers, bool debug) {

		bool found;

		//check		 support
		std::vector<vk::LayerProperties> supportedLayers = vk::enumerateInstanceLayerProperties();
		if (debug) {
			PGE_CORE_TRACE("Logical device Device can support the folowing extensions: { ");

			for (vk::LayerProperties supportedLayer : supportedLayers) {
				PGE_CORE_INFO("{0}", supportedLayer.layerName);
			}
			PGE_CORE_INFO("}");
		}

		/**
		* quadratic search for layers
		*/
		for (const char* layer : layers)
		{
			found = false;

			for (vk::LayerProperties supportedLayer : supportedLayers)
			{
				if (strcmp(layer, supportedLayer.layerName) == 0) {
					found = true;
					if (debug) {
						PGE_CORE_INFO("layer: {0} is supported", layer);
					}
				}
			}
			if (!found) {
				if (debug) {
					PGE_CORE_INFO("layer: {0} is not supported", layer);
				}
				return false;
			}
		}

		return true;
	}


	void create_logical_device(const vk::PhysicalDevice physicalDevice, vk::Device& device, vk::SurfaceKHR& surface, const bool debug, vk::Queue& graphicsQueue,
		vk::Queue& presentQueue) {

		QueueFamilyIndices m_indices = findQueueFamilies(physicalDevice, debug, surface);

		std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
		std::set<uint32_t> uniqueQueueFamilies = { m_indices.graphicsFamily.value(), m_indices.presentFamily.value() };

		float queuePriority = 1.0f;

		for (uint32_t queueFamily : uniqueQueueFamilies) {
			queueCreateInfos.push_back({ vk::DeviceQueueCreateFlags(),queueFamily,1, &queuePriority });
		}


		auto deviceFeatures = vk::PhysicalDeviceFeatures();
		auto createInfo = vk::DeviceCreateInfo(vk::DeviceCreateFlags(), static_cast<uint32_t>(queueCreateInfos.size()), queueCreateInfos.data());

		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = static_cast<uint32_t>(requestedExtensions.size());
		createInfo.ppEnabledExtensionNames = requestedExtensions.data();

		std::vector<const char*> layers;

		createInfo.enabledLayerCount = static_cast<uint32_t>(layers.size());
		createInfo.ppEnabledLayerNames = layers.data();


		if (debug) {
			layers.push_back("VK_LAYER_KHRONOS_validation");
		}

		if (!supported(layers, debug)) {
			PGE_CORE_ERROR("not supported");
		}

		createInfo.enabledLayerCount = static_cast<uint32_t>(layers.size());
		createInfo.ppEnabledLayerNames = layers.data();

		try {
			if (debug) {
				PGE_CORE_INFO("logical device created succsfully");
			}
			device = physicalDevice.createDevice(createInfo);
		}
		catch (vk::SystemError err) {
			PGE_CORE_ERROR("failed to create logical device!");
		}

		graphicsQueue = device.getQueue(m_indices.graphicsFamily.value(), 0);
		presentQueue = device.getQueue(m_indices.presentFamily.value(), 0);

	}


}