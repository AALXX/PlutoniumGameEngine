#pragma once
#include "pphd.h"

#include <vulkan/vulkan.hpp>

namespace PGE_VULKAN {

	//debug callback

	VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData
	) {
		PGE_CORE_ERROR("validation layer: {0}", pCallbackData->pMessage);

		return VK_FALSE;
	}

	vk::DebugUtilsMessengerEXT  make_debug_messenger(vk::Instance& instance, vk::DispatchLoaderDynamic& dldi) {

		vk::DebugUtilsMessengerCreateInfoEXT createInfo = vk::DebugUtilsMessengerCreateInfoEXT(
			vk::DebugUtilsMessengerCreateFlagsEXT(),
			vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError,
			vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance,
			debugCallback,
			nullptr
		);

		return instance.createDebugUtilsMessengerEXT(createInfo, nullptr, dldi);

	}

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
}