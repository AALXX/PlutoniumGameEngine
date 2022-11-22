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
		virtual void DrawIndexed();
		virtual void SubmitVertices(glm::mat3x3& Recivedvertices) override;
		virtual void WindowResized(int width, int height) override;

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
		std::vector<vk::Image> swapChainImages;
		vk::Format swapChainFormat;
		vk::Extent2D swapChainExtent;

		void CreateVulkanDevice();

	};

}