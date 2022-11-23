#pragma once

#include <vector>
#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>

//namespace for creation functions/definitions etc.
namespace PGE_VULKAN {

	bool supported(std::vector<const char*>& extensions, std::vector<const char*>& layers, bool debug);

	vk::Instance make_instance(bool debug, const char* applicationName);
}