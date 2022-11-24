#pragma once
#include <Platofrm/VulkanApi/Device/QueueFamilies.h>
#include <Platofrm/VulkanApi/Swapchain/Frame.h>

namespace PGE_VULKAN {
	struct commandBufferInputChunk {
		vk::Device device;
		vk::CommandPool commandPool;
		std::vector<SwapChainFrame>& frames;
	};


	vk::CommandPool make_command_pool(vk::Device device, vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface, bool debug) {
		QueueFamilyIndices queueFamilyIndices = findQueueFamilies(physicalDevice, surface, debug);

		vk::CommandPoolCreateInfo poolInfo;
		poolInfo.flags = vk::CommandPoolCreateFlags() | vk::CommandPoolCreateFlagBits::eResetCommandBuffer;
		poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

		try {
			return device.createCommandPool(poolInfo);
		}
		catch (vk::SystemError err) {

			if (debug) {
				PGE_CORE_INFO("Failed to create Command Pool");
			}

			return nullptr;
		}
	}

	vk::CommandBuffer make_command_buffers(commandBufferInputChunk inputChunk, bool debug) {

		vk::CommandBufferAllocateInfo allocInfo = {};
		allocInfo.commandPool = inputChunk.commandPool;
		allocInfo.level = vk::CommandBufferLevel::ePrimary;
		allocInfo.commandBufferCount = 1;

		//Make a command buffer for each frame
		for (int i = 0; i < inputChunk.frames.size(); ++i) {
			try {
				inputChunk.frames[i].commandBuffer = inputChunk.device.allocateCommandBuffers(allocInfo)[0];

				if (debug) {
					PGE_CORE_INFO("Allocated command buffer for frame ");
				}
			}
			catch (vk::SystemError err) {

				if (debug) {
					PGE_CORE_INFO("Failed to allocate command buffer for frame");

				}
			}
		}


		//Make a "main" command buffer for the engine
		try {
			vk::CommandBuffer commandBuffer = inputChunk.device.allocateCommandBuffers(allocInfo)[0];

			if (debug) {
				PGE_CORE_INFO("Allocated main command buffer ");

			}

			return commandBuffer;
		}
		catch (vk::SystemError err) {

			if (debug) {
				PGE_CORE_INFO("Failed to allocate main command buffer ");

			}

			return nullptr;
		}
	}

}