#pragma once
namespace PGE_VULKAN {

	uint32_t findMemoryType(uint32_t typeFilter, vk::MemoryPropertyFlags properties, vk::PhysicalDevice physicalDevice) {
		vk::PhysicalDeviceMemoryProperties memProprieties = physicalDevice.getMemoryProperties();

		for (uint32_t i = 0; i < memProprieties.memoryTypeCount; i++)
		{
			if ((typeFilter & (1 << i)) && (memProprieties.memoryTypes[i].propertyFlags & properties) == properties)
			{
				return i;
			}
		}

		PGE_CORE_ERROR("failed to find suitable memory type!");
	}

	void create_Buffer(vk::Device device, vk::PhysicalDevice physicalDevice,  vk::DeviceSize size, vk::BufferUsageFlags usage, vk::MemoryPropertyFlags properties, 
		vk::Buffer& buffer, vk::DeviceMemory& bufferMemory)
	{
		vk::BufferCreateInfo bufferInfo = {};
		bufferInfo.size = size;
		bufferInfo.usage = usage;
		bufferInfo.sharingMode = vk::SharingMode::eExclusive;

		try
		{
			buffer = device.createBuffer(bufferInfo);
		}
		catch (vk::SystemError err)
		{
			PGE_CORE_ERROR("failed to create buffer!");
		}

		vk::MemoryRequirements memRequirements = device.getBufferMemoryRequirements(buffer);

		vk::MemoryAllocateInfo allocInfo = {};
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties, physicalDevice);

		try
		{
			bufferMemory = device.allocateMemory(allocInfo);
		}
		catch (vk::SystemError err)
		{
			PGE_CORE_ERROR("failed to allocate buffer memory!");
		}

		device.bindBufferMemory(buffer, bufferMemory, 0);
	}

	void copyBuffer(vk::Queue graphicsQueue, vk::CommandPool commandPool, vk::Device device, vk::Buffer srcBuffer, vk::Buffer dstBuffer, vk::DeviceSize size) {
		vk::CommandBufferAllocateInfo allocInfo = {};
		allocInfo.level = vk::CommandBufferLevel::ePrimary;
		allocInfo.commandPool = commandPool;
		allocInfo.commandBufferCount = 1;

		vk::CommandBuffer  commandBuffer = device.allocateCommandBuffers(allocInfo)[0];

		vk::CommandBufferBeginInfo beginInfo = {};
		beginInfo.flags = vk::CommandBufferUsageFlagBits::eOneTimeSubmit;

		commandBuffer.begin(beginInfo);

		vk::BufferCopy copyRegion = {};
		copyRegion.srcOffset = 0; // Optional
		copyRegion.dstOffset = 0; // Optional
		copyRegion.size = size; 
		commandBuffer.copyBuffer(srcBuffer, dstBuffer, copyRegion);

		commandBuffer.end();


		vk::SubmitInfo submitInfo{};
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;
		graphicsQueue.submit(submitInfo, nullptr);
		graphicsQueue.waitIdle();

		device.freeCommandBuffers(commandPool, commandBuffer);
	}

}