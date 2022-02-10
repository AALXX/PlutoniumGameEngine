#pragma once
#include "pphd.h"

#include <vulkan/vulkan.hpp>

namespace PGE_VULKAN {

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

	bool isSuitable(const vk::PhysicalDevice& device, const bool debug) {
		if (debug) {
			PGE_CLIENT_TRACE("Checking if device is sutable");
		}

		const std::vector<const char*> requestedExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

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
		return true;
	}

	vk::PhysicalDevice choose_phisical_device(vk::Instance& instance, bool debug) {
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
			if (isSuitable(device, debug)) {
				return device;
			}
		}

		return nullptr;

	}
}