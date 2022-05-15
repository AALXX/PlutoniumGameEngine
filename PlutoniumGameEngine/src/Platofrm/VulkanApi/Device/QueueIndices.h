#pragma once
#include "pphd.h"

#include <vulkan/vulkan.hpp>

namespace PGE_VULKAN{


	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};


	QueueFamilyIndices findQueueFamilies(const vk::PhysicalDevice physicalDevice, const bool debug, const vk::SurfaceKHR surface) {
		QueueFamilyIndices indices;

		auto queueFamilies = physicalDevice.getQueueFamilyProperties();

		int i = 0;
		for (const auto& queueFamily : queueFamilies)
		{
			if (queueFamily.queueCount > 0 && queueFamily.queueFlags & vk::QueueFlagBits::eGraphics) {
				indices.graphicsFamily = i;
			}


			if (queueFamily.queueCount > 0 && physicalDevice.getSurfaceSupportKHR(i, surface)) {
				indices.presentFamily = i;
			}

			if (indices.isComplete()) {
				break;
			}

			i++;
		}

		return indices;
	}


}