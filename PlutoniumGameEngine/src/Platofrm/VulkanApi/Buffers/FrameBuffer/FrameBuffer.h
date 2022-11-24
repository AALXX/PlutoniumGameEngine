#pragma once
#include <Platofrm/VulkanApi/Swapchain/Frame.h>


namespace PGE_VULKAN {
	struct frameBufferInput
	{
		vk::Device device;
		vk::RenderPass renderpass;
		vk::Extent2D swapchainExtent;
	};

	void make_framebuffers(frameBufferInput inputChunk, std::vector<SwapChainFrame>& frames, bool debug);
}