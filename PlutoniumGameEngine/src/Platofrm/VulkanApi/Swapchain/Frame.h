#pragma once
#include <vulkan/vulkan.hpp>

namespace PGE_VULKAN {

	struct SwapChainFrame
	{
		vk::Image image;
		vk::ImageView imageView;
		vk::Framebuffer frameBuffers;
		vk::CommandBuffer commandBuffer;
		vk::Semaphore imageAvailable, renderFinished;
		vk::Fence inFlight;
	};

}