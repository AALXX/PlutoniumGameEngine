#pragma once
#include <Vulkan/vulkan.hpp>
namespace PGE_VULKAN {
	
	vk::Semaphore make_semaphore(vk::Device device, bool debug);

	vk::Fence make_fence(vk::Device device, bool debug);
}