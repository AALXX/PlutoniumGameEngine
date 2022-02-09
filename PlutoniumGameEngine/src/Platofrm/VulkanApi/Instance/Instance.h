#pragma once
#include "pphd.h"

#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

//namespace for creation functions/definitions etc.
namespace PGE_VULKAN {

	vk::Instance make_instance(bool debug, const char* applicationName) {

		if (debug) {
			PGE_CORE_INFO("Making an instance");
		}

		/*
		* An instance stores all per-application state info, it is a vulkan handle
		* (An opaque integer or pointer value used to refer to a Vulkan object)
		* side note: in the vulkan.hpp binding it's a wrapper class around a handle
		
		*/

		/*
		* We can scan the system and check which version it will support up to,
		* as of vulkan 1.1
		*
		* VkResult vkEnumerateInstanceVersion(
			uint32_t*                                   pApiVersion);
		*/

		uint32_t version{ 0 };
		vkEnumerateInstanceVersion(&version);

		if (debug) {
			PGE_CORE_INFO("System can support vulkan Variant: {0}", VK_API_VERSION_VARIANT(version));
			PGE_CORE_INFO("System can support vulkan Major: {0}", VK_API_VERSION_MAJOR(version));
			PGE_CORE_INFO("System can support vulkan Minor: {0}", VK_API_VERSION_MINOR(version));
			PGE_CORE_INFO("System can support vulkan Patch: {0}", VK_API_VERSION_PATCH(version));
		}

		/*
		* We can then either use this version
		* (We should just be sure to set the patch to 0 for best compatibility/stability)
		*/
		version &= ~(0xFFFU);

		/*
		* vulkan application info
		*/

		vk::ApplicationInfo appInfo = vk::ApplicationInfo(
			applicationName,
			version,
			"Plutonium Engine",
			version,
			version
		);

		/*
		* Everything with Vulkan is "opt-in", so we need to query which extensions glfw needs
		* in order to interface with vulkan.
		*/
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

		if (debug) {
			PGE_CORE_INFO("extensions to be requested: { ");

			for (const char* extensionName : extensions) {
				PGE_CORE_INFO("{0}", extensionName);
			}
			PGE_CORE_INFO("}");
		}

		/*
		*
		* vulkan instance info
		*/
		vk::InstanceCreateInfo createInfo = vk::InstanceCreateInfo(
			vk::InstanceCreateFlags(),
			&appInfo,
			0, nullptr, // enabled layers
			static_cast<uint32_t>(extensions.size()), extensions.data() // enabled extensions
		);


		try {
			return vk::createInstance(createInfo);
		}
		catch (vk::SystemError err) {
			if (debug) {
				PGE_CORE_ERROR("Failed to create Instance!");
			}
			return nullptr;
		}
	}
}