#include "pphd.h"
#include "VulkanRendererApi.h"

#include "Platofrm/VulkanApi/Instance/Instance.h"
#include "Platofrm/VulkanApi/Logging/Logging.h"
#include "Platofrm/VulkanApi/Suraface/Surface.h"
#include "Platofrm/VulkanApi/SwapChain/SwapChain.h"
#include "Platofrm/VulkanApi/Device/Device.h"
#include "Platofrm/VulkanApi/GraphicsPipeline/GraphicsPipeline.h"
#include <Platofrm/VulkanApi/FrameBuffers/FrameBuffers.h>
#include <Platofrm/VulkanApi/Drawing/SyncObjects.h>
#include <Platofrm/VulkanApi/Buffers/Buffer.h>
#include <Platofrm/VulkanApi/Buffers/VertexBuffer.h>


namespace PGE_VULKAN {

	bool VulkanRendererAPI::Init()
	{

		makeInstance();
		createSurface(m_windowHandle);
		makeDevice();
		createSwapChain();
		createImageViews();
		createRenderPass();
		createGraphicsPipeline();
		createFrameBuffers();
		createCommandPool();
		createVertexBuffer();
		createCommandBuffer();
		createSyncObjects();


		return true;
	}

	void VulkanRendererAPI::GetWindow(GLFWwindow* window, int windowWidth, int windowHeight)
	{
		m_windowHandle = window;
		m_windowHandleWidth = windowWidth;
		m_windowHandleHeight = windowHeight;

	}

	void VulkanRendererAPI::SetClearColor(const glm::vec4& color)
	{
	}

	void VulkanRendererAPI::Clear()
	{
	}

	void VulkanRendererAPI::DrawIndexed()
	{
		drawFrame();

	}

	void VulkanRendererAPI::SubmitVertices(glm::mat3x3& Recivedvertices)
	{
	}

	void VulkanRendererAPI::WindowResized(int width, int height)
	{
		framebufferResized = true;
	}


	bool VulkanRendererAPI::release()
	{
		device.waitIdle();


		cleanupSwapChain();

		device.destroyBuffer(vertexBuffer);
		device.freeMemory(vertexBufferMemory);

		for (size_t i = 0; i < _maxFramesInFlight; i++) {
			device.destroySemaphore(renderFinishedSemaphore[i]);
			device.destroySemaphore(imageAvailableSemaphore[i]);
			device.destroyFence(inFlightFences[i]);
		}

		device.destroyCommandPool(commandPool);


		instance.destroySurfaceKHR(surface);


		device.destroy();

		instance.destroyDebugUtilsMessengerEXT(debugMessenger, nullptr, dldi);


		instance.destroy();
		return true;
	}

	void VulkanRendererAPI::makeInstance()
	{
		instance = make_instance(isDebug, "Plutonium engine");

		dldi = vk::DispatchLoaderDynamic(instance, vkGetInstanceProcAddr);

		if (isDebug) {
			debugMessenger = make_debug_messenger(instance, dldi);
		}
	}

	void VulkanRendererAPI::createSurface(GLFWwindow* windwoHandle)
	{

		surface = create_surface(instance, windwoHandle);
	}

	void VulkanRendererAPI::makeDevice()
	{
		//chose physical device
		physicalDevice = choose_phisical_device(instance, isDebug, surface);

		//create logical devices
		create_logical_device(physicalDevice, device, surface, isDebug, graphicsQueue, presentQueue);
	}

	void VulkanRendererAPI::createSwapChain()
	{
		create_swap_chain(physicalDevice, surface, m_windowHandleWidth, m_windowHandleHeight, isDebug, device,
			swapChain, swapChainImages, swapChainImageFormat, swapChainExtent);
	}

	void VulkanRendererAPI::cleanupSwapChain() {
		for (auto framebuffer : swapChainFrameBuffers) {
			device.destroyFramebuffer(framebuffer);
		}

		device.freeCommandBuffers(commandPool, commandBuffer);

		device.destroyPipeline(graphicsPipeline);
		device.destroyPipelineLayout(pipelineLayout);
		device.destroyRenderPass(renderPass);

		for (auto imageView : swapChainImageViews) {
			device.destroyImageView(imageView);
		}

		device.destroySwapchainKHR(swapChain);
	}

	void VulkanRendererAPI::recreateSwapChain()
	{
		int width = 0, height = 0;
		while (width == 0 || height == 0) {
			glfwGetFramebufferSize(m_windowHandle, &width, &height);
			glfwWaitEvents();
		}

		device.waitIdle();

		cleanupSwapChain();

		createSwapChain();
		createImageViews();
		createRenderPass();
		createGraphicsPipeline();
		createFrameBuffers();
		createCommandBuffer();
	}

	void VulkanRendererAPI::createImageViews()
	{
		create_image_views(swapChainImages, swapChainImageViews, swapChainImageFormat, device, isDebug);
	}

	void VulkanRendererAPI::createRenderPass() {
		create_render_pass(renderPass, device, swapChainImageFormat);
	}

	void VulkanRendererAPI::createGraphicsPipeline() {
		create_graphics_pipeline(device, swapChainExtent, pipelineLayout, renderPass, graphicsPipeline, isDebug);
	}

	void VulkanRendererAPI::createFrameBuffers()
	{
		create_frame_buffers(swapChainFrameBuffers, swapChainImageViews, renderPass, swapChainExtent, device, isDebug);
	}

	void VulkanRendererAPI::createCommandPool()
	{
		create_command_pool(commandPool, device, physicalDevice, surface, isDebug);
	}

	void VulkanRendererAPI::createCommandBuffer()
	{
		create_command_buffer(commandBuffer, swapChainFrameBuffers, commandPool, device, renderPass, swapChainExtent, graphicsPipeline, vertexBuffer, vertices);
	}

	void VulkanRendererAPI::createSyncObjects()
	{
		create_sync_objects(imageAvailableSemaphore, renderFinishedSemaphore, _maxFramesInFlight, inFlightFences, device);
	}

	void VulkanRendererAPI::drawFrame() {
		device.waitForFences(1, &inFlightFences[currentFrame], VK_TRUE, std::numeric_limits<uint64_t>::max());
		device.resetFences(1, &inFlightFences[currentFrame]);

		uint32_t imageIndex;
		try {
			vk::ResultValue result = device.acquireNextImageKHR(swapChain, std::numeric_limits<uint64_t>::max(),
				imageAvailableSemaphore[currentFrame], nullptr);
			imageIndex = result.value;
		}
		catch (vk::OutOfDateKHRError err) {
			recreateSwapChain();

			return;
		}
		catch (vk::SystemError err) {
			throw std::runtime_error("failed to acquire swap chain image!");
		}

		//draw to the image by submitting to command buffer
		vk::SubmitInfo submitInfo = {};

		vk::Semaphore waitSemaphores[] = { imageAvailableSemaphore[currentFrame] };
		vk::PipelineStageFlags waitStages[] = { vk::PipelineStageFlagBits::eColorAttachmentOutput };
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;

		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer[imageIndex];

		vk::Semaphore signalSemaphores[] = { renderFinishedSemaphore[currentFrame] };
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSemaphores;

		device.resetFences(1, &inFlightFences[currentFrame]);


		try
		{
			graphicsQueue.submit(submitInfo, inFlightFences[currentFrame]);
		}
		catch (vk::SystemError err)
		{
			PGE_CORE_ERROR("failed to submit draw command buffer!");
		}

		vk::PresentInfoKHR presentInfo = {};
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSemaphores;

		vk::SwapchainKHR swapChains[] = { swapChain };
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapChains;
		presentInfo.pImageIndices = &imageIndex;

		vk::Result resultPresent;
		try {
			resultPresent = presentQueue.presentKHR(presentInfo);
		}
		catch (vk::OutOfDateKHRError err) {
			resultPresent = vk::Result::eErrorOutOfDateKHR;
		}
		catch (vk::SystemError err) {
			throw std::runtime_error("failed to present swap chain image!");
		}

		if (resultPresent == vk::Result::eSuboptimalKHR || resultPresent == vk::Result::eSuboptimalKHR || framebufferResized) {
			PGE_CORE_INFO("swap chain out of date/suboptimal/window resized - recreating");
			framebufferResized = false;
			recreateSwapChain();
			return;
		}

		currentFrame = (currentFrame + 1) % _maxFramesInFlight;
		
	}
	
	void VulkanRendererAPI::createVertexBuffer()
	{
		create_vertex_buffer(graphicsQueue, commandPool,vertexBuffer, vertexBufferMemory, vertices, device, physicalDevice);
	}

}
