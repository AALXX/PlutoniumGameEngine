#pragma once
#include "Platofrm/VulkanApi/Device/QueueIndices.h"

namespace PGE_VULKAN {

	void create_frame_buffers(std::vector<vk::Framebuffer>& swapChainFrameBuffers, std::vector<vk::ImageView>& swapChainImageViews, vk::RenderPass& renderPass, vk::Extent2D swapChainExtent, vk::Device& device, bool isDebug) {
		swapChainFrameBuffers.resize(swapChainImageViews.size());

		for (size_t i = 0; i < swapChainImageViews.size(); i++)
		{
			vk::ImageView attachments[] = { swapChainImageViews[i] };

			vk::FramebufferCreateInfo framebufferInfo{};
			framebufferInfo.renderPass = renderPass;
			framebufferInfo.attachmentCount = 1;
			framebufferInfo.pAttachments = attachments;
			framebufferInfo.width = swapChainExtent.width;
			framebufferInfo.height = swapChainExtent.height;
			framebufferInfo.layers = 1;

			try {
				swapChainFrameBuffers[i] = device.createFramebuffer(framebufferInfo);
				
				if(isDebug) {
					PGE_CORE_TRACE("Framebuffer created succesfully");

				}


			}
			catch (vk::SystemError err) {
				PGE_CORE_ERROR("failed to create framebuffer!");
			}
		}
	}

	void create_command_pool(vk::CommandPool& commandPool, vk::Device& device, vk::PhysicalDevice& physicalDevice, vk::SurfaceKHR surface, bool isDebug) {
		QueueFamilyIndices queueFamilyIndices = findQueueFamilies(physicalDevice, isDebug, surface);

		/*command pool is allocating graphics commands*/
		vk::CommandPoolCreateInfo poolInfo = {};
		poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

		try {
			commandPool = device.createCommandPool(poolInfo);
		}
		catch (vk::SystemError err) {
			PGE_CORE_ERROR("failed to create command pool!");
		}
	}

	void create_command_buffer(std::vector<vk::CommandBuffer> &commandBuffers, std::vector<vk::Framebuffer> swapChainFrameBuffers, vk::CommandPool commandPool,
		vk::Device device, vk::RenderPass renderPass, vk::Extent2D swapChainExtent, vk::Pipeline graphicsPipeline, vk::Buffer vertexBuffer, std::vector<Vertex> vertices) {
		//each command buffer holds the chain of instructions used in render pass
		//individual command buffer must e made for each framebuffer
		commandBuffers.resize(swapChainFrameBuffers.size());

		vk::CommandBufferAllocateInfo cmdBufferAllocInfo{};
		vk::CommandBufferAllocateInfo allocInfo = {};
		allocInfo.commandPool = commandPool;
		allocInfo.level = vk::CommandBufferLevel::ePrimary;
		allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();

		try {
			commandBuffers = device.allocateCommandBuffers(allocInfo);
		}
		catch (vk::SystemError err) {
			PGE_CORE_ERROR("failed to allocate command buffers!");
		}

		for (size_t i = 0; i < commandBuffers.size(); i++)
		{
			vk::CommandBufferBeginInfo commandBufferBeginInfo{};
			commandBufferBeginInfo.flags = vk::CommandBufferUsageFlagBits::eSimultaneousUse;

			try {
				commandBuffers[i].begin(commandBufferBeginInfo);
			}
			catch (vk::SystemError err) {
				PGE_CORE_ERROR("failed to begin recording command buffer!");
			}

			vk::RenderPassBeginInfo renderPassBeginInfo{};
			renderPassBeginInfo.renderPass = renderPass;
			renderPassBeginInfo.framebuffer = swapChainFrameBuffers[i];
			renderPassBeginInfo.renderArea.offset.x = 0;
			renderPassBeginInfo.renderArea.offset.y = 0;
			renderPassBeginInfo.renderArea.extent = swapChainExtent;

			vk::ClearValue clearColor = { std::array<float, 4>{0.0f, 0.0f, 0.0f, 1.0f} };
			renderPassBeginInfo.clearValueCount = 1;
			renderPassBeginInfo.pClearValues = &clearColor;

			commandBuffers[i].beginRenderPass(renderPassBeginInfo, vk::SubpassContents::eInline);
			commandBuffers[i].bindPipeline(vk::PipelineBindPoint::eGraphics, graphicsPipeline);
			
			vk::Buffer vertexBuffers[] = { vertexBuffer };
			vk::DeviceSize offsets[] = { 0 };
			commandBuffers[i].bindVertexBuffers(0, 1, vertexBuffers, offsets);
			commandBuffers[i].draw(static_cast<uint32_t>(vertices.size()), 1, 0, 0);
			
			commandBuffers[i].endRenderPass();

			try
			{
				commandBuffers[i].end();
			}
			catch (vk::SystemError err)
			{
				PGE_CORE_ERROR("failed to record command buffer!");

			}
		}

	}
}