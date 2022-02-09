#pragma once
#include <vulkan/vulkan.hpp>

namespace PGE {

	class GraphicsEngine
	{

	public:
		GraphicsEngine();

		// initialize engine
		bool init();

		bool release();

		~GraphicsEngine();

	public:
		static GraphicsEngine* get();
	private:

		bool isDebug = true;

		vk::Instance instance{ nullptr };

		void makeInstance();
	};
}

