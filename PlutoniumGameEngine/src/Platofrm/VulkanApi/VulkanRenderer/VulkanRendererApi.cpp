#include "pphd.h"
#include "VulkanRendererApi.h"

#include "Platofrm/VulkanApi/Instance/Instance.h"
#include "Platofrm/VulkanApi/Logging/Logging.h"
#include "Platofrm/VulkanApi/Suraface/Surface.h"
#include "Platofrm/VulkanApi/SwapChain/SwapChain.h"
#include "Platofrm/VulkanApi/Device/Device.h"
#include "Platofrm/VulkanApi/GraphicsPipeline/GraphicsPipeline.h"
#include <Platofrm/VulkanApi/FrameBuffers/FrameBuffers.h>


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

	bool VulkanRendererAPI::release()
	{

		device.destroyCommandPool(commandPool);

		for (auto framebuffer : swapChainFrameBuffers) {
			device.destroyFramebuffer(framebuffer);
		}


		device.destroyPipeline(graphicsPipeline);
		device.destroyPipelineLayout(pipelineLayout);
		device.destroyRenderPass(renderPass);

		for (auto imageView : swapChainImageViews) {
			device.destroyImageView(imageView);
		}
		
		
		device.destroySwapchainKHR(swapChain);

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
		create_frame_buffers(swapChainFrameBuffers, swapChainImageViews,renderPass,swapChainExtent,device, isDebug);
	}

	void VulkanRendererAPI::createCommandPool()
	{
		create_command_pool(commandPool, device, physicalDevice, surface, isDebug);
	}

	void VulkanRendererAPI::createCommandBuffer()
	{
		create_command_buffer(commandBuffer, swapChainFrameBuffers, commandPool, device, renderPass, swapChainExtent, graphicsPipeline);
	}

}
