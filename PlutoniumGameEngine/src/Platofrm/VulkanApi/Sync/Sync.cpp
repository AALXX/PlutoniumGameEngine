#include "pphd.h"
#include "Sync.h"

namespace PGE_VULKAN {


	vk::Semaphore make_semaphore(vk::Device device, bool debug)
	{
		vk::SemaphoreCreateInfo semaphoreInfo = {};
		semaphoreInfo.flags = vk::SemaphoreCreateFlags();

		try
		{
			return device.createSemaphore(semaphoreInfo);
		}
		catch (vk::SystemError err)
		{
			if (debug) {
				PGE_CORE_INFO("failed to create semaphore");
			}

			return nullptr;
		}
	}
	
	vk::Fence make_fence(vk::Device device, bool debug)
	{
		vk::FenceCreateInfo fenceInfo = {};
		fenceInfo.flags = vk::FenceCreateFlags() | vk::FenceCreateFlagBits::eSignaled;

		try
		{
			return device.createFence(fenceInfo);
		}
		catch (vk::SystemError err)
		{
			if (debug) {
				PGE_CORE_INFO("failed to create fence");
			}

			return nullptr;
		}
	}
}
