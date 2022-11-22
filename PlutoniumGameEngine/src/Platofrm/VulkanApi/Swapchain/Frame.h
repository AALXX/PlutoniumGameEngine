#pragma once
#include "pphd.h"
#include <vulkan/vulkan.hpp>

namespace PGE_VULKAN {

	struct SwapChainFrame
	{
		vk::Image image;
		vk::ImageView imageView;
	};

}