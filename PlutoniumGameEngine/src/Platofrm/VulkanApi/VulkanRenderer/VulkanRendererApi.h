#pragma once
#include <vulkan/vulkan.hpp>

#include "PlutoniumGameEngine/GraphicsEngine/Renderer/RendererApi.h"


namespace PGE_VULKAN {


	class VulkanRendererAPI : public PGE::RendererAPI {

	public:

		virtual bool Init() override;

		virtual void GetWindow(GLFWwindow* window) override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed() {};

		bool isDebug = true;

		virtual bool release() override;



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

		GLFWwindow* m_windowHandle;

		void createSurface(GLFWwindow* windwoHandle);

	private:
		//device related
		vk::PhysicalDevice physicalDevice{ nullptr };

		vk::Device device;

		vk::Queue graphicsQueue;
		vk::Queue presentQueue;

		void makeDevice();

	};
}