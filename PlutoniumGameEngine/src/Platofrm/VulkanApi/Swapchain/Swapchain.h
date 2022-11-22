#pragma once
#include "pphd.h"
#include <vulkan/vulkan.hpp>
#include <Platofrm/VulkanApi/Logging/Logging.h>
#include <Platofrm/VulkanApi/Device/QueueFamilies.h>
#include <Platofrm/VulkanApi/Swapchain/Frame.h>

namespace PGE_VULKAN {
	struct SwapChainSupportDetails
	{
		vk::SurfaceCapabilitiesKHR capabilities;
		std::vector<vk::SurfaceFormatKHR> formats;
		std::vector<vk::PresentModeKHR> presentModes;
	};

	struct SwapChainBundle {
		vk::SwapchainKHR swapchain;
		std::vector<SwapChainFrame> frames;
		vk::Format format;
		vk::Extent2D extent;
	};

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

		support.formats = device.getSurfaceFormatsKHR(surface);

		if (debug) {

			for (vk::SurfaceFormatKHR supportedFormat : support.formats) {
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

		vk::SurfaceFormatKHR format = choose_swapchain_surface_format(support.formats);

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

		std::vector<vk::Image> images = logicalDevice.getSwapchainImagesKHR(bundle.swapchain);
		bundle.frames.resize(images.size());

		for (size_t i = 0; i < images.size(); ++i)
		{
			vk::ImageViewCreateInfo createInfo = {};
			createInfo.image = images[i];
			createInfo.viewType = vk::ImageViewType::e2D;
			createInfo.components.r = vk::ComponentSwizzle::eIdentity;
			createInfo.components.g = vk::ComponentSwizzle::eIdentity;
			createInfo.components.b = vk::ComponentSwizzle::eIdentity;
			createInfo.components.a = vk::ComponentSwizzle::eIdentity;
			createInfo.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
			createInfo.subresourceRange.baseMipLevel = 0;
			createInfo.subresourceRange.levelCount = 1;
			createInfo.subresourceRange.baseArrayLayer = 0;
			createInfo.subresourceRange.layerCount = 1;
			createInfo.format = format.format;

			bundle.frames[i].image = images[i];
			bundle.frames[i].imageView = logicalDevice.createImageView(createInfo);
		}

		bundle.format = format.format;
		bundle.extent = extent;

		return bundle;

	}

}