
#pragma once
#include <vulkan/vulkan.hpp>
#include <Platofrm/VulkanApi/Logging/Logging.h>
#include <Platofrm/VulkanApi/Device/QueueFamilies.h>


namespace PGE_VULKAN {

	bool checkDeviceExtensionSupport(
		const vk::PhysicalDevice& device,
		const std::vector<const char*>& requestedExtensions,
		const bool& debug
	) {

		/*
		* Check if a given physical device can satisfy a list of requested device
		* extensions.
		*/

		std::set<std::string> requiredExtensions(requestedExtensions.begin(), requestedExtensions.end());

		if (debug) {
			PGE_CORE_INFO("Device can support extensions:\n");

		}

		for (vk::ExtensionProperties& extension : device.enumerateDeviceExtensionProperties()) {

			if (debug) {
				PGE_CORE_INFO(" {0} ", extension.extensionName);

			}

			//remove this from the list of required extensions (set checks for equality automatically)
			requiredExtensions.erase(extension.extensionName);
		}

		//if the set is empty then all requirements have been satisfied
		return requiredExtensions.empty();
	}

	bool isSuitable(const vk::PhysicalDevice& device, const bool debug) {

		if (debug) {
			PGE_CORE_INFO("Checking if device is suitable\n");
		}

		/*
		* A device is suitable if it can present to the screen, ie support
		* the swapchain extension
		*/
		const std::vector<const char*> requestedExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

		if (debug) {
			PGE_CORE_INFO("We are requesting device extensions: ");


			for (const char* extension : requestedExtensions) {
				PGE_CORE_INFO("{0} ", extension);
			}

		}

		if (bool extensionsSupported = checkDeviceExtensionSupport(device, requestedExtensions, debug)) {

			if (debug) {
				PGE_CORE_INFO("Device can support the requested extensions!\n");
			}
		}
		else {

			if (debug) {
				PGE_CORE_INFO("Device can't support the requested extensions!\n");
			}

			return false;
		}
		return true;
	}

	vk::PhysicalDevice choose_physical_device(const vk::Instance& instance, const bool debug) {

		/*
		* Choose a suitable physical device from a list of candidates.
		* Note: Physical devices are neither created nor destroyed, they exist
		* independently to the program.
		*/

		if (debug) {
			PGE_CORE_INFO("Choosing Physical Device\n");
		}

		/*
		* ResultValueType<std::vector<PhysicalDevice, PhysicalDeviceAllocator>>::type
			Instance::enumeratePhysicalDevices( Dispatch const & d )
		  std::vector<vk::PhysicalDevice> instance.enumeratePhysicalDevices( Dispatch const & d = static/default )
		*/
		std::vector<vk::PhysicalDevice> availableDevices = instance.enumeratePhysicalDevices();

		if (debug) {
			PGE_CORE_INFO("There are {0} physical devices available on this system\n", availableDevices.size());
		}

		/*
		* check if a suitable device can be found
		*/
		for (vk::PhysicalDevice device : availableDevices) {

			if (debug) {
				log_device_properties(device);
			}
			if (isSuitable(device, debug)) {
				return device;
			}
		}

		return nullptr;
	}

	vk::Device create_logical_device(vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface, bool debug) {

		/*
		* Create an abstraction around the GPU
		*/

		/*
		* At time of creation, any required queues will also be created,
		* so queue create info must be passed in.
		*/

		QueueFamilyIndices indices = findQueueFamilies(physicalDevice, surface, debug);
		std::vector<uint32_t> uniqueIndices;

		uniqueIndices.push_back(indices.graphicsFamily.value());

		if (indices.graphicsFamily.value() != indices.presentFamily.value())
		{
			uniqueIndices.push_back(indices.presentFamily.value());
		}

		float queuePriority = 1.0f;
		/*
		* VULKAN_HPP_CONSTEXPR DeviceQueueCreateInfo( VULKAN_HPP_NAMESPACE::DeviceQueueCreateFlags flags_            = {},
												uint32_t                                     queueFamilyIndex_ = {},
												uint32_t                                     queueCount_       = {},
												const float * pQueuePriorities_ = {} ) VULKAN_HPP_NOEXCEPT
		*/
		std::vector<vk::DeviceQueueCreateInfo> queueCreateInfo;

		for (uint32_t queueFamilyIndex : uniqueIndices)
		{
			queueCreateInfo.push_back(vk::DeviceQueueCreateInfo(vk::DeviceQueueCreateFlags(), queueFamilyIndex, 1, &queuePriority));
		}

		std::vector<const char*> deviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME
		};

		/*
		* Device features must be requested before the device is abstracted,
		* therefore we only pay for what we need.
		*/

		vk::PhysicalDeviceFeatures deviceFeatures = vk::PhysicalDeviceFeatures();

		/*
		* VULKAN_HPP_CONSTEXPR DeviceCreateInfo( VULKAN_HPP_NAMESPACE::DeviceCreateFlags flags_                         = {},
										   uint32_t                                queueCreateInfoCount_          = {},
										   const VULKAN_HPP_NAMESPACE::DeviceQueueCreateInfo * pQueueCreateInfos_ = {},
										   uint32_t                                            enabledLayerCount_ = {},
										   const char * const * ppEnabledLayerNames_                              = {},
										   uint32_t             enabledExtensionCount_                            = {},
										   const char * const * ppEnabledExtensionNames_                          = {},
										   const VULKAN_HPP_NAMESPACE::PhysicalDeviceFeatures * pEnabledFeatures_ = {} )
		*/
		std::vector<const char*> enabledLayers;
		if (debug) {
			enabledLayers.push_back("VK_LAYER_KHRONOS_validation");
		}

		vk::DeviceCreateInfo deviceInfo = vk::DeviceCreateInfo(
			vk::DeviceCreateFlags(),
			queueCreateInfo.size(), queueCreateInfo.data(),
			enabledLayers.size(), enabledLayers.data(),
			deviceExtensions.size(), deviceExtensions.data(),
			&deviceFeatures
		);

		try {
			vk::Device device = physicalDevice.createDevice(deviceInfo);
			if (debug) {
				PGE_CORE_INFO("GPU has been successfully abstracted!\n");

			}
			return device;
		}
		catch (vk::SystemError err) {
			if (debug) {
				PGE_CORE_INFO("Device creation failed!\n");

				return nullptr;
			}
		}
		return nullptr;
	}

	std::array<vk::Queue, 2> get_queues(vk::PhysicalDevice physicalDevice, vk::Device device, vk::SurfaceKHR surface, bool debug) {

		QueueFamilyIndices indices = findQueueFamilies(physicalDevice, surface, debug);

		return { {
				device.getQueue(indices.graphicsFamily.value(), 0),
				device.getQueue(indices.presentFamily.value(), 0),
			} };
	}

}