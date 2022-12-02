#include "pphd.h"
#include "VulkanRendererApi.h"
#include <Platofrm/VulkanApi/VulkanInstance/VulkanInstance.h>
#include <Platofrm/VulkanApi/Logging/Logging.h>
#include <Platofrm/VulkanApi/Device/Device.h>
#include <Platofrm/VulkanApi/Swapchain/Swapchain.h>
#include <Platofrm/VulkanApi/VulkanGraphicsPipeline/VulkanGraphicsPipeline.h>
#include <Platofrm/VulkanApi/Buffers/FrameBuffer/FrameBuffer.h>
#include <Platofrm/VulkanApi/Buffers/CommandBuffer/CommandBuffer.h>
#include <Platofrm/VulkanApi/Sync/Sync.h>




namespace PGE_VULKAN {

	bool VulkanRendererAPI::Init()
	{
		CreateVulkanInstance();
		CreateVulkanDevice();

		CreateVulkanGraphicsPipeline();

		Finish_Setup();

		return true;
	}

	//void VulkanRendererAPI::GetWindow(GLFWwindow* window, int windowWidth, int windowHeight)
	//{
	//	m_windowHandle = window;
	//	m_windowHandleWidth = windowWidth;
	//	m_windowHandleHeight = windowHeight;

	//}

	void VulkanRendererAPI::SetClearColor(const glm::vec4& color)
	{
	}

	void VulkanRendererAPI::Clear()
	{
	}

	void VulkanRendererAPI::DrawIndexed()
	{
		device.waitForFences(1, &swapchainFrames[frameNumber].inFlight, VK_TRUE, UINT64_MAX);
		device.resetFences(1, &swapchainFrames[frameNumber].inFlight);

		uint32_t imageIndex{ device.acquireNextImageKHR(swapChain, UINT64_MAX, swapchainFrames[frameNumber].imageAvailable, nullptr).value };

		vk::CommandBuffer commandBuffer = swapchainFrames[frameNumber].commandBuffer;
		record_draw_commands(commandBuffer, imageIndex);


		vk::SubmitInfo submitInfo = {};

		vk::Semaphore waitSemaphores[] = { swapchainFrames[frameNumber].imageAvailable };
		vk::PipelineStageFlags waitStages[] = { vk::PipelineStageFlagBits::eColorAttachmentOutput };
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;

		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;

		vk::Semaphore signalSemaphores[] = { swapchainFrames[frameNumber].imageAvailable };
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSemaphores;

		try {
			graphicsQueue.submit(submitInfo, swapchainFrames[frameNumber].inFlight);
		}
		catch (vk::SystemError err) {

			if (isDebug) {
				PGE_CORE_INFO("failed to submit draw command buffer!");
			}
		}

		vk::PresentInfoKHR presentInfo = {};
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSemaphores;

		vk::SwapchainKHR swapChains[] = { swapChain };
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapChains;

		presentInfo.pImageIndices = &imageIndex;

		presentQueue.presentKHR(presentInfo);

		frameNumber = (frameNumber + 1) % maxFramesInFlight;
	}


	void VulkanRendererAPI::SetViewPort(uint32_t x, uint32_t  y, uint32_t width, uint32_t height)
	{
	}


	void VulkanRendererAPI::CreateVulkanInstance()
	{
		instance = make_instance(isDebug, "Plutonium engine");
		dldi = vk::DispatchLoaderDynamic(instance, vkGetInstanceProcAddr);

		if (isDebug) {
			debugMessenger = make_debug_messenger(instance, dldi);
		}

		VkSurfaceKHR c_stye_surface;

		//if (glfwCreateWindowSurface(instance, m_windowHandle, nullptr, &c_stye_surface) != VK_SUCCESS) {
		//	if (isDebug) {
		//		PGE_CORE_ERROR("failed to abstact glfw surface for Vulkan \n");
		//	}
		//}
		//else if (isDebug) {
		//	PGE_CORE_ERROR("Sucessfully abstact glfw surface for Vulkan \n");

		//}

		surface = c_stye_surface;
	}

	void VulkanRendererAPI::CreateVulkanDevice()
	{
		physicalDevice = choose_physical_device(instance, isDebug);
		device = create_logical_device(physicalDevice, surface,isDebug);
		std::array<vk::Queue, 2> queues = get_queues(physicalDevice, device, surface, isDebug);

		graphicsQueue = queues[0];
		presentQueue = queues[1];
		SwapChainBundle bundle = create_swapchain(device, physicalDevice, surface, m_windowHandleWidth, m_windowHandleHeight, isDebug);
		swapChain = bundle.swapchain;
		swapchainFrames = bundle.frames;
		swapChainFormat = bundle.format;
		swapChainExtent = bundle.extent;
		maxFramesInFlight = static_cast<int>(swapchainFrames.size()); 
		frameNumber = 0;
	}

	void VulkanRendererAPI::CreateVulkanGraphicsPipeline() {
		
		GraphicsPipelineInBundle specification = {};
		specification.device = device;
		specification.vertexFilepath = "D:/Projects/PlutoniumGameEngine/bin/Debug-windows-x86_64/Sandbox/vertx.spv";
		specification.fragmentFilepath = "D:/Projects/PlutoniumGameEngine/bin/Debug-windows-x86_64/Sandbox/fragment.spv";
		specification.swapchainExtent = swapChainExtent;

		specification.swapchainImageFormat = swapChainFormat;

		GraphicsPipelineOutBundle output = create_graphics_pipeline(
			specification, isDebug
		);

		pipelineLayout = output.layout;
		renderpass = output.renderpass;
		pipeline = output.pipeline;
	}

	void VulkanRendererAPI::Finish_Setup()
	{
		frameBufferInput framebufferInput;
		framebufferInput.device = device;
		framebufferInput.renderpass = renderpass;
		framebufferInput.swapchainExtent = swapChainExtent;

		make_framebuffers(framebufferInput, swapchainFrames, isDebug);

		commandPool = make_command_pool(device, physicalDevice, surface, isDebug);
		commandBufferInputChunk commandBufferInput = { device, commandPool, swapchainFrames };
		mainCommandBuffer = make_command_buffers(commandBufferInput, isDebug);

		for (SwapChainFrame& frame : swapchainFrames)
		{
			frame.inFlight = make_fence(device, isDebug);
			frame.imageAvailable = make_semaphore(device, isDebug);
			frame.renderFinished = make_semaphore(device, isDebug);
		}
	}

	void VulkanRendererAPI::record_draw_commands(vk::CommandBuffer commandBuffer, uint32_t imageIndex)
	{
		vk::CommandBufferBeginInfo beginInfo = {};

		try {
			commandBuffer.begin(beginInfo);
		}
		catch (vk::SystemError err) {
			if (isDebug) {
				PGE_CORE_INFO("Failed to begin recording command buffer!");
			}
		}

		vk::RenderPassBeginInfo renderPassInfo = {};
		renderPassInfo.renderPass = renderpass;
		renderPassInfo.framebuffer = swapchainFrames[imageIndex].frameBuffers;
		renderPassInfo.renderArea.offset.x = 0;
		renderPassInfo.renderArea.offset.y = 0;
		renderPassInfo.renderArea.extent = swapChainExtent;

		vk::ClearValue clearColor = { std::array<float, 4>{1.0f, 0.5f, 0.25f, 1.0f} };
		renderPassInfo.clearValueCount = 1;
		renderPassInfo.pClearValues = &clearColor;

		commandBuffer.beginRenderPass(&renderPassInfo, vk::SubpassContents::eInline);

		commandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline);

		commandBuffer.draw(3, 1, 0, 0);

		commandBuffer.endRenderPass();

		try {
			commandBuffer.end();
		}
		catch (vk::SystemError err) {

			if (isDebug) {
				PGE_CORE_INFO("failed to record command buffer!");

			}
		}
	}

	bool VulkanRendererAPI::release() {

		device.waitIdle();

		device.destroyCommandPool(commandPool);

		device.destroyPipeline(pipeline);
		device.destroyPipelineLayout(pipelineLayout);
		device.destroyRenderPass(renderpass);

		for (SwapChainFrame frame : swapchainFrames) {
			device.destroyImageView(frame.imageView);
			device.destroyFramebuffer(frame.frameBuffers);
			device.destroyFence(frame.inFlight);
			device.destroySemaphore(frame.imageAvailable);
			device.destroySemaphore(frame.renderFinished);
		}

		device.destroySwapchainKHR(swapChain);
		device.destroy();

		instance.destroySurfaceKHR(surface);

		if (isDebug) {
			instance.destroyDebugUtilsMessengerEXT(debugMessenger, nullptr, dldi);
		}

		instance.destroy();
		return true;
	}
}
