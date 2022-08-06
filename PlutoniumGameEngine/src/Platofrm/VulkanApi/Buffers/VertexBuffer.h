#pragma once
#include "Platofrm/VulkanApi/Buffers/Buffer.h"


namespace PGE_VULKAN {

	void create_vertex_buffer(vk::Queue graphicsQueue, vk::CommandPool commandPool, vk::Buffer& vertexBuffer, vk::DeviceMemory& vertexBufferMemory, std::vector<Vertex> vertices, vk::Device device, vk::PhysicalDevice physicalDevice) {
		vk::DeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

		vk::Buffer stagingBuffer;
		vk::DeviceMemory stagingBufferMemory;
		create_Buffer(device, physicalDevice, bufferSize, 
			vk::BufferUsageFlagBits::eTransferSrc, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent,
			stagingBuffer, stagingBufferMemory);

		void* data = device.mapMemory(stagingBufferMemory, 0, bufferSize);
		memcpy(data, vertices.data(), (size_t)bufferSize);
		device.unmapMemory(stagingBufferMemory);

		create_Buffer(device, physicalDevice, 
			bufferSize, vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eVertexBuffer, 
			vk::MemoryPropertyFlagBits::eDeviceLocal, vertexBuffer, vertexBufferMemory);

		copyBuffer(graphicsQueue, commandPool, device, stagingBuffer, vertexBuffer, bufferSize);

		device.destroyBuffer(stagingBuffer);
		device.freeMemory(stagingBufferMemory);
	}


}