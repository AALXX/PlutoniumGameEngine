#pragma once

namespace PGE_VULKAN {
	vk::SurfaceKHR  create_surface(vk::Instance &instance, GLFWwindow* &window) {
		VkSurfaceKHR rawSurface;

		if (glfwCreateWindowSurface(instance, window, nullptr, &rawSurface) != VK_SUCCESS) {
			PGE_CORE_ERROR("Failed create Surface");
		}

		return rawSurface;
	}
}