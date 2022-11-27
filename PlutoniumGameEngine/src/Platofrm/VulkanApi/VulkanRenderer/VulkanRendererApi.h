#pragma once
#include <vulkan/vulkan.hpp>

#include "PlutoniumGameEngine/GraphicsEngine/Renderer/RendererApi.h"
#include <Platofrm/VulkanApi/Swapchain/Frame.h>


namespace PGE_VULKAN {
	class VulkanRendererAPI : public PGE::Renderer {

	public:

		virtual bool Init() override;

		//virtual void GetWindow(GLFWwindow* window, int windowWidth, int windowHeight) override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed();
		virtual void WindowResized(int width, int height) override;

		bool isDebug = true;

		virtual bool release() override;

	private:
		//Window reference
		//GLFWwindow* m_windowHandle;

		int m_windowHandleWidth;
		int m_windowHandleHeight;
	
	private:
		//instance-related

		//instance setup
		void CreateVulkanInstance();

		//vulkan instance
		vk::Instance instance{ nullptr };

		//debug callback
		vk::DebugUtilsMessengerEXT debugMessenger{ nullptr };

		//dynamic instance dispatcher
		vk::DispatchLoaderDynamic dldi;

		//window surface
		vk::SurfaceKHR surface;

	private:
		//device related
		vk::PhysicalDevice physicalDevice{ nullptr };

		vk::Device device{ nullptr };

		vk::Queue graphicsQueue{ nullptr };
		vk::Queue presentQueue{ nullptr };

		vk::SwapchainKHR swapChain;
		std::vector<SwapChainFrame> swapchainFrames;
		vk::Format swapChainFormat;
		vk::Extent2D swapChainExtent;

		void CreateVulkanDevice();
	private:
		//graphics Pipeline

		vk::PipelineLayout pipelineLayout;
		vk::RenderPass renderpass;
		vk::Pipeline pipeline;

		void CreateVulkanGraphicsPipeline();

		void Finish_Setup();

	private:
		//command buffer
		vk::CommandPool commandPool;
		vk::CommandBuffer mainCommandBuffer;

	private:
		//sync
		int maxFramesInFlight, frameNumber;
	private:
		//render
		void record_draw_commands(vk::CommandBuffer  CommandBuffer, uint32_t imageIndex);
	};

}