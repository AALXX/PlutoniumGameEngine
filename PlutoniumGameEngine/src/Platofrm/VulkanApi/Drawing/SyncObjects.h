#pragma once

namespace PGE_VULKAN {

	void create_sync_objects(std::vector<vk::Semaphore> &imageAvailableSemaphore, std::vector<vk::Semaphore> &renderFinishedSemaphore, int maxFramesInFlight, 
		std::vector<vk::Fence> &inFlightFences, vk::Device device) {
		imageAvailableSemaphore.resize(maxFramesInFlight);
		renderFinishedSemaphore.resize(maxFramesInFlight);
		inFlightFences.resize(maxFramesInFlight);

		try
		{
			for (size_t i = 0; i < maxFramesInFlight; i++)
			{
				imageAvailableSemaphore[i] = device.createSemaphore({});
				renderFinishedSemaphore[i] = device.createSemaphore({});
				inFlightFences[i] = device.createFence({ vk::FenceCreateFlagBits::eSignaled });
			}
		}
		catch (vk::SystemError  err)
		{
			PGE_CORE_ERROR("failed to create synchronization objects for a frame!");
		}
	}
}