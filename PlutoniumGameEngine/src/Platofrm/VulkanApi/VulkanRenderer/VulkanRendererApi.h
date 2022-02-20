#pragma once
#include <vulkan/vulkan.hpp>

#include "PlutoniumGameEngine/GraphicsEngine/Renderer/RendererApi.h"



namespace PGE_VULKAN {


	class VulkanRendererAPI : public PGE::RendererAPI {

	public:

		virtual bool Init() override;

		virtual void GetWindow(GLFWwindow* window, int windowWidth, int windowHeight) override;
		
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed() {};

		bool isDebug = true;

		virtual bool release() override;

	private:
		//Window reference
		GLFWwindow* m_windowHandle;

		int m_windowHandleWidth;
		int m_windowHandleHeight;

	private:
		//instance-related

		//instance setup
		void makeInstance();
	
		//vulkan instance
		vk::Instance instance{ nullptr };

		//debug callback
		vk::DebugUtilsMessengerEXT debugMessenger{ nullptr };

		//dynamic instance dispatcher
		vk::DispatchLoaderDynamic dldi;
	public:
		//vulkan surface
		vk::SurfaceKHR surface;


		void createSurface(GLFWwindow* windwoHandle);

	private:
		//device related
		vk::PhysicalDevice physicalDevice{ nullptr };

		vk::Device device;

		vk::Queue graphicsQueue;
		vk::Queue presentQueue;

		void makeDevice();
	private:

		vk::SwapchainKHR swapChain;
		std::vector<vk::Image> swapChainImages;
		vk::Format swapChainImageFormat;
		vk::Extent2D swapChainExtent;

		std::vector<vk::ImageView> swapChainImageViews;

		void createSwapChain();
		void createImageViews();
	};
}