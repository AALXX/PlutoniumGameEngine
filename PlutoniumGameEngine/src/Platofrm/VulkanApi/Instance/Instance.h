#pragma once
#include "pphd.h"

#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

//namespace for creation functions/definitions etc.
namespace PGE_VULKAN {

	bool supported(std::vector<const char*>& extensions, std::vector<const char*>& layers, bool debug) {

		//check extension support

		std::vector<vk::ExtensionProperties> supportedExtensions = vk::enumerateInstanceExtensionProperties();

		if (debug) {
			extensions.push_back("VK_EXT_debug_utils");
		}

		if (debug) {
			PGE_CORE_INFO("Device can support the folowing extensions: { ");

			for (vk::ExtensionProperties supportedExtension : supportedExtensions) {
				PGE_CORE_INFO("{0}", supportedExtension.extensionName);
			}
			PGE_CORE_INFO("}");
		}

		bool found;

		/**
		 * quadratic search for extension
		 */
		for (const char* extension : extensions)
		{
			found = false;

			for (vk::ExtensionProperties supportedExtension : supportedExtensions)
			{
				if (strcmp(extension, supportedExtension.extensionName) == 0) {
					found = true;
					if (debug) {
						PGE_CORE_INFO("Extension: {0} is supported", extension);
					}
				}
			}
			if (!found) {
				if (debug) {
					PGE_CORE_INFO("Extension: {0} is not supported", extension);
				}
				return false;
			}
		}

		//check		 support
		std::vector<vk::LayerProperties> supportedLayers = vk::enumerateInstanceLayerProperties();
		if (debug) {
			PGE_CORE_INFO("Device can support the folowing extensions: { ");

			for (vk::LayerProperties supportedLayers : supportedLayers) {
				PGE_CORE_INFO("{0}", supportedLayers.layerName);
			}
			PGE_CORE_INFO("}");
		}

		/**
		* quadratic search for layers
		*/
		for (const char* layer : layers)
		{
			found = false;

			for (vk::LayerProperties supportedLayer: supportedLayers)
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

		std::vector<const char*> layers;

		if (debug) {
			layers.push_back("VK_LAYER_KHRONOS_validation");
		}

		if (!supported(extensions, layers, debug)) {
			return nullptr;
		}

		/*
		* vulkan instance info
		*/
		vk::InstanceCreateInfo createInfo = vk::InstanceCreateInfo(vk::InstanceCreateFlags(), &appInfo,
			static_cast<uint32_t>(layers.size()), layers.data(), // enabled layers
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