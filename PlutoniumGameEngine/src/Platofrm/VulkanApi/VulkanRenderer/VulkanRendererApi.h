#pragma once
#include <vulkan/vulkan.hpp>

#include "PlutoniumGameEngine/GraphicsEngine/Renderer/RendererApi.h"

namespace PGE_VULKAN {
	class VulkanRendererAPI : public PGE::RendererAPI {

	public:

		virtual bool Init() override;

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
	private:
		//vulkan surface
		vk::SurfaceKHR surface;

		void createSurface();

	private:
		//device related
		vk::PhysicalDevice physicalDevice{ nullptr };

		vk::Device device;

		vk::Queue graphicsQueue;

		void makeDevice();
	};
}