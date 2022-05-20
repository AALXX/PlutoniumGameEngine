#pragma once

namespace PGE_VULKAN {

	uint32_t findMemoryType(uint32_t typeFilter, vk::MemoryPropertyFlags properties, vk::PhysicalDevice& physicalDevice) {
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

	void create_vertex_buffer(vk::Buffer& vertexBuffer, vk::DeviceMemory &vertexBufferMemory, std::vector<Vertex> vertices, vk::Device device, vk::PhysicalDevice &physicalDevice) {
		vk::BufferCreateInfo bufferInfo = {};
		bufferInfo.size = sizeof(vertices[0]) * vertices.size();
		bufferInfo.usage = vk::BufferUsageFlagBits::eVertexBuffer;
		bufferInfo.sharingMode = vk::SharingMode::eExclusive;

		try
		{
			vertexBuffer = device.createBuffer(bufferInfo);
		}
		catch (vk::SystemError err)
		{
			PGE_CORE_ERROR("failed to create vertex buffer!");
		}

		vk::MemoryRequirements memRequirements = device.getBufferMemoryRequirements(vertexBuffer);

		vk::MemoryAllocateInfo allocInfo = {};
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent, physicalDevice);
	
		try
		{
			vertexBufferMemory = device.allocateMemory(allocInfo);
		}
		catch (vk::SystemError err)
		{
			PGE_CORE_ERROR("failed to allocate vertex buffer memory!");
		}

		device.bindBufferMemory(vertexBuffer, vertexBufferMemory, 0);

		void* data = device.mapMemory(vertexBufferMemory, 0, bufferInfo.size);
		memcpy(data, vertices.data(), (size_t)bufferInfo.size);
		device.unmapMemory(vertexBufferMemory);
	}



}