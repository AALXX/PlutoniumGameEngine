#pragma once
#include <vulkan/vulkan.hpp>



namespace PGE_VULKAN {
	struct  GraphicsPipelineInBundle
	{
		vk::Device device;
		std::string vertexFilepath;
		std::string fragmentFilepath;
		vk::Extent2D swapchainExtent;
		vk::Format swapchainImageFormat;
	};

	struct GraphicsPipelineOutBundle
	{
		vk::PipelineLayout layout;
		vk::RenderPass renderpass;
		vk::Pipeline pipeline;
	};

	vk::PipelineLayout make_pipeline_layout(vk::Device device, bool debug);

	vk::RenderPass make_renderpass(vk::Device device, vk::Format swapchainImageFormat, bool debug);

	GraphicsPipelineOutBundle create_graphics_pipeline(GraphicsPipelineInBundle& specification, bool debug);
}