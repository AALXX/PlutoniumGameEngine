
#pragma once
#include "pphd.h"
#include <vulkan/vulkan.hpp>
#include <Platofrm/VulkanApi/Logging/Logging.h>

namespace PGE_VULKAN {
	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	struct SwapChainSupportDetails
	{
		vk::SurfaceCapabilitiesKHR capabilities;
		std::vector<vk::SurfaceFormatKHR> format;
		std::vector<vk::PresentModeKHR> presentModes;
	};

	struct SwapChainBundle {
		vk::SwapchainKHR swapchain;
		std::vector<vk::Image> images;
		vk::Format format;
		vk::Extent2D extent;
	};

	void log_device_properties(const vk::PhysicalDevice& device) {
		/*
		* void vkGetPhysicalDeviceProperties(
			VkPhysicalDevice                            physicalDevice,
			VkPhysicalDeviceProperties*                 pProperties);
		*/

		vk::PhysicalDeviceProperties properties = device.getProperties();

		/*
		* typedef struct VkPhysicalDeviceProperties {
			uint32_t                            apiVersion;
			uint32_t                            driverVersion;
			uint32_t                            vendorID;
			uint32_t                            deviceID;
			VkPhysicalDeviceType                deviceType;
			char                                deviceName[VK_MAX_PHYSICAL_DEVICE_NAME_SIZE];
			uint8_t                             pipelineCacheUUID[VK_UUID_SIZE];
			VkPhysicalDeviceLimits              limits;
			VkPhysicalDeviceSparseProperties    sparseProperties;
			} VkPhysicalDeviceProperties;
		*/

		PGE_CORE_INFO("Device name: {0}", properties.deviceName);


		PGE_CORE_INFO("Device type: ");

		switch (properties.deviceType) {

		case (vk::PhysicalDeviceType::eCpu):
			PGE_CORE_INFO("CPU\n");
			break;

		case (vk::PhysicalDeviceType::eDiscreteGpu):
			PGE_CORE_INFO("Discrete GPU\n");
			break;

		case (vk::PhysicalDeviceType::eIntegratedGpu):
			PGE_CORE_INFO("Integrated GPU\n");
			break;

		case (vk::PhysicalDeviceType::eVirtualGpu):
			PGE_CORE_INFO("Virtual GPU\n");
			break;

		default:
			PGE_CORE_INFO("other\n");
		}
	}

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

	QueueFamilyIndices findQueueFamilies(vk::PhysicalDevice device, vk::SurfaceKHR surface, bool debug) {
		QueueFamilyIndices indices;

		std::vector<vk::QueueFamilyProperties> queueFamilies = device.getQueueFamilyProperties();

		if (debug) {
			PGE_CORE_INFO("There are {0} queue families available on the system.\n", queueFamilies.size());

		}

		int i = 0;
		for (vk::QueueFamilyProperties queueFamily : queueFamilies) {

			/*
			* // Provided by VK_VERSION_1_0
				typedef struct VkQueueFamilyProperties {
				VkQueueFlags    queueFlags;
				uint32_t        queueCount;
				uint32_t        timestampValidBits;
				VkExtent3D      minImageTransferGranularity;
				} VkQueueFamilyProperties;
				queueFlags is a bit mask of VkQueueFlagBits indicating capabilities of the queues in this queue family.
				queueCount is the unsigned integer count of queues in this queue family. Each queue family must support
				at least one queue.
				timestampValidBits is the unsigned integer count of meaningful bits in the timestamps written via
				vkCmdWriteTimestamp. The valid range for the count is 36..64 bits, or a value of 0,
				indicating no support for timestamps. Bits outside the valid range are guaranteed to be zeros.
				minImageTransferGranularity is the minimum granularity supported for image transfer
				operations on the queues in this queue family.
			*/

			/*
			* // Provided by VK_VERSION_1_0
				typedef enum VkQueueFlagBits {
				VK_QUEUE_GRAPHICS_BIT = 0x00000001,
				VK_QUEUE_COMPUTE_BIT = 0x00000002,
				VK_QUEUE_TRANSFER_BIT = 0x00000004,
				VK_QUEUE_SPARSE_BINDING_BIT = 0x00000008,
				} VkQueueFlagBits;
			*/

			if (queueFamily.queueFlags & vk::QueueFlagBits::eGraphics) {
				indices.graphicsFamily = i;

				if (debug) {
					PGE_CORE_INFO("Queue Family {0} is suitable for graphics\n", i);
				}
			}

			if (device.getSurfaceSupportKHR(i, surface)) {
				indices.presentFamily = i;

				if (debug) {
					PGE_CORE_INFO("Queue Family {0} is suitable for presenting\n", i);
				}
			}

			if (indices.isComplete()) {
				break;
			}

			i++;
		}

		return indices;
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


	vk::SurfaceFormatKHR choose_swapchain_surface_format(std::vector<vk::SurfaceFormatKHR> formats) {
		for (vk::SurfaceFormatKHR format : formats)
		{
			if (format.format == vk::Format::eB8G8R8A8Unorm && format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
				return format;
			}
		}

		return formats[0];
	}

	vk::PresentModeKHR choose_swapchain_present_mode(std::vector<vk::PresentModeKHR> presentModes) {
		for (vk::PresentModeKHR presentMode : presentModes) {
			if (presentMode == vk::PresentModeKHR::eMailbox) {
				return presentMode;
			}
		}

		return vk::PresentModeKHR::eFifo;
	}

	vk::Extent2D choose_swapchain_extent(uint32_t width, uint32_t height, vk::SurfaceCapabilitiesKHR capabilities) {
		if (capabilities.currentExtent != UINT32_MAX) {
			return capabilities.currentExtent;
		}
		else {
			vk::Extent2D extent = { width, height };

			extent.width = std::min(
				capabilities.maxImageExtent.width,
				std::max(capabilities.minImageExtent.width, extent.width)
			);

			extent.height = std::min(
				capabilities.maxImageExtent.height,
				std::max(capabilities.minImageExtent.height, extent.height)
			);

			return extent;
		}
	}


	SwapChainSupportDetails query_swapchain_support(vk::PhysicalDevice device, vk::SurfaceKHR surface, bool debug) {
		SwapChainSupportDetails support;

		support.capabilities = device.getSurfaceCapabilitiesKHR(surface);

		if (debug)
		{
			PGE_CORE_INFO("swapchain can suport the folowing surface capabilities \n");

			PGE_CORE_INFO("\tminimum image count: {0} \n", support.capabilities.minImageCount);
			PGE_CORE_INFO("\tminimum image count: {0} \n", support.capabilities.maxImageCount);

			PGE_CORE_INFO("\tminimum supported extent: \n");
			PGE_CORE_INFO("\twidth: {0} \n", support.capabilities.minImageExtent.width);
			PGE_CORE_INFO("\theight: {0} \n", support.capabilities.minImageExtent.height);

			PGE_CORE_INFO("\tmaximum supported extent: \n");

			PGE_CORE_INFO("\theight: {0} \n", support.capabilities.maxImageExtent.width);
			PGE_CORE_INFO("\theight: {0} \n", support.capabilities.maxImageExtent.height);

			PGE_CORE_INFO("\tmaximum image array layers:  \n", support.capabilities.maxImageArrayLayers);

			PGE_CORE_INFO("\tsupported transforms: \n");
			std::vector<std::string> stringList = log_transform_bits(support.capabilities.supportedTransforms);
			for (std::string line : stringList) {
				PGE_CORE_INFO("\t\t {0},", line);
			}

			PGE_CORE_INFO("\tcurrent transform: \n");
			stringList = log_transform_bits(support.capabilities.currentTransform);
			for (std::string line : stringList) {
				PGE_CORE_INFO("\t\t {0},", line);
			}

			PGE_CORE_INFO("\tsupported alpha operations: \n");
			stringList = log_alpha_composite_bits(support.capabilities.supportedCompositeAlpha);
			for (std::string line : stringList) {
				PGE_CORE_INFO("\t\t {0},", line);
			}

			PGE_CORE_INFO("\tsupported image usage: \n");
			stringList = log_image_usage_bits(support.capabilities.supportedUsageFlags);
			for (std::string line : stringList) {
				PGE_CORE_INFO("\t\t {0},", line);
			}
		}

		support.format = device.getSurfaceFormatsKHR(surface);

		if (debug) {

			for (vk::SurfaceFormatKHR supportedFormat : support.format) {
				/*
				* typedef struct VkSurfaceFormatKHR {
					VkFormat           format;
					VkColorSpaceKHR    colorSpace;
				} VkSurfaceFormatKHR;
				*/

				PGE_CORE_INFO("supported pixel format: {0},", vk::to_string(supportedFormat.format));

				PGE_CORE_INFO("supported color space: {0},", vk::to_string(supportedFormat.colorSpace));
			}
		}

		support.presentModes = device.getSurfacePresentModesKHR(surface);

		for (vk::PresentModeKHR presentMode : support.presentModes) {
			PGE_CORE_INFO("supported color space: {0},", log_present_mode(presentMode));

		}

		return support;
	}

	SwapChainBundle create_swapchain(vk::Device logicalDevice, vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface, int width, int height, bool debug) {
		SwapChainSupportDetails support = query_swapchain_support(physicalDevice, surface, debug);

		vk::SurfaceFormatKHR format = choose_swapchain_surface_format(support.format);

		vk::PresentModeKHR presentMode = choose_swapchain_present_mode(support.presentModes);

		vk::Extent2D extent = choose_swapchain_extent(width, height, support.capabilities);

		uint32_t imageCount = std::min(
			support.capabilities.maxImageCount,
			support.capabilities.maxImageCount + 1
		);

		vk::SwapchainCreateInfoKHR createInfo = vk::SwapchainCreateInfoKHR(
			vk::SwapchainCreateFlagsKHR(), surface, imageCount, format.format, format.colorSpace, extent, 1, vk::ImageUsageFlagBits::eColorAttachment

		);

		QueueFamilyIndices indices = findQueueFamilies(physicalDevice, surface, debug);
		uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

		if (indices.graphicsFamily != indices.presentFamily) {
			createInfo.imageSharingMode = vk::SharingMode::eConcurrent;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else {
			createInfo.imageSharingMode = vk::SharingMode::eExclusive;
		}

		createInfo.preTransform = support.capabilities.currentTransform;
		createInfo.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;

		createInfo.oldSwapchain = vk::SwapchainKHR(nullptr);

		SwapChainBundle bundle{};
		try {
			bundle.swapchain = logicalDevice.createSwapchainKHR(createInfo);
			PGE_CORE_INFO("Sucessfull create swap chain!");
		}
		catch (vk::SystemError err) {
			PGE_CORE_ERROR("failed to create swap chain!");
		}

		bundle.images = logicalDevice.getSwapchainImagesKHR(bundle.swapchain);
		bundle.format = format.format;
		bundle.extent = extent;

		return bundle;

	}
}