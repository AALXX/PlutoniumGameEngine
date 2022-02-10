#pragma once
#include <vulkan/vulkan.hpp>

namespace PGE {

	class GraphicsEngine
	{

	public:
		GraphicsEngine();

		// initialize engine
		bool init();

		bool isDebug = true;

		bool release();

		~GraphicsEngine();

	public:
		static GraphicsEngine* get();
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
		//device related
		vk::PhysicalDevice physicalDevice{ nullptr };

		void makeDevice();
	};
}

