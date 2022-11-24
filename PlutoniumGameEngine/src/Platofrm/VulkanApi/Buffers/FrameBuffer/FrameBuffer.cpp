#include "pphd.h"
#include "FrameBuffer.h"

namespace PGE_VULKAN {

	void make_framebuffers(frameBufferInput inputChunk, std::vector<SwapChainFrame>& frames, bool debug)
	{
		for (int i = 0; i < frames.size(); ++i) {
			std::vector<vk::ImageView> attachments = {
				frames[i].imageView
			};

			vk::FramebufferCreateInfo framebufferInfo;
			framebufferInfo.flags = vk::FramebufferCreateFlags();
			framebufferInfo.renderPass = inputChunk.renderpass;
			framebufferInfo.attachmentCount = attachments.size();
			framebufferInfo.pAttachments = attachments.data();
			framebufferInfo.width = inputChunk.swapchainExtent.width;
			framebufferInfo.height = inputChunk.swapchainExtent.height;
			framebufferInfo.layers = 1;

			try {
				frames[i].frameBuffers = inputChunk.device.createFramebuffer(framebufferInfo);

				if (debug) {
					PGE_CORE_INFO("Created framebuffer for frame: {0}", i);
				}
			}
			catch (vk::SystemError err) {
				if (debug) {
					PGE_CORE_INFO("Failed to create framebuffer for frame");
				}
			}
		}
	}
}