#pragma once
#include "pphd.h"

#include <fstream>

#include <vulkan/vulkan.hpp>

namespace PGE_VULKAN {

	static std::vector<char> readFile(const std::string& filename) {
		std::ifstream file(filename, std::ios::ate | std::ios::binary);

		if (!file.is_open()) {
			PGE_CORE_ERROR("failed to open file!");
		}

		size_t fileSize = (size_t)file.tellg();
		std::vector<char> buffer(fileSize);

		file.seekg(0);
		file.read(buffer.data(), fileSize);

		file.close();

		return buffer;
	}

	vk::ShaderModule createShaderModule(const std::vector<char>& code, vk::Device& device) {
		try {
			return device.createShaderModule({
				vk::ShaderModuleCreateFlags(),
				code.size(),
				reinterpret_cast<const uint32_t*>(code.data())
				});
		}
		catch (vk::SystemError err) {
			PGE_CORE_ERROR("failed to create shader module");
		}
	}

	void create_graphics_pipeline(vk::Device &device, vk::Extent2D &swapChainExtent, vk::PipelineLayout& pipelineLayout, vk::RenderPass &renderPass,
		vk::Pipeline& graphicsPipeline, bool debug) {

		auto vertShaderCode = readFile("D:/Projects/PlutoniumGameEngine/bin/Debug-windows-x86_64/Sandbox/vertx.spv");
		auto fragShaderCode = readFile("D:/Projects/PlutoniumGameEngine/bin/Debug-windows-x86_64/Sandbox/fragment.spv");


		//compile/parse spir-v data
		auto vertShaderModule = createShaderModule(vertShaderCode, device);
		auto fragShaderModule = createShaderModule(fragShaderCode, device);


		//create shader stages
		vk::PipelineShaderStageCreateInfo shaderStages[] = {
			{
				vk::PipelineShaderStageCreateFlags(),
				vk::ShaderStageFlagBits::eVertex,
				vertShaderModule,
				"main"
			},
			{
				vk::PipelineShaderStageCreateFlags(),
				vk::ShaderStageFlagBits::eFragment,
				fragShaderModule,
				"main"
			}
		};

		//vertex fetch
		vk::PipelineVertexInputStateCreateInfo vertexInputInfo = {};
		vertexInputInfo.vertexBindingDescriptionCount = 0;
		vertexInputInfo.vertexAttributeDescriptionCount = 0;

		auto bindingDescription = Vertex::getBindingDescription();
		auto attributeDescriptions = Vertex::getAttributeDescriptions();

		vertexInputInfo.vertexBindingDescriptionCount = 1;
		vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
		vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
		vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();
		
		//input assembly
		vk::PipelineInputAssemblyStateCreateInfo inputAssembly = {};
		inputAssembly.topology = vk::PrimitiveTopology::eTriangleList;
		inputAssembly.primitiveRestartEnable = VK_FALSE;

		//viewport
		vk::Viewport viewport = {};
		viewport.x = 0.0f;
		viewport.y = 0.0f;
		viewport.width = (float)swapChainExtent.width;
		viewport.height = (float)swapChainExtent.height;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;


		//scissor is a test which is applied after render 
		vk::Rect2D scissor = {};
		scissor.offset.setX(0);
		scissor.offset.setY(0);
		scissor.extent = swapChainExtent;

		//viewport and scissor together describe a viewport state
		vk::PipelineViewportStateCreateInfo viewportState = {};
		viewportState.viewportCount = 1;
		viewportState.pViewports = &viewport;
		viewportState.scissorCount = 1;
		viewportState.pScissors = &scissor;


		//rasterizer, interpolates data between vertices to fill in fragments
		vk::PipelineRasterizationStateCreateInfo rasterizer = {};
		rasterizer.depthClampEnable = VK_FALSE;
		rasterizer.rasterizerDiscardEnable = VK_FALSE;
		rasterizer.polygonMode = vk::PolygonMode::eFill;
		rasterizer.lineWidth = 1.0f;
		rasterizer.cullMode = vk::CullModeFlagBits::eBack;
		rasterizer.frontFace = vk::FrontFace::eClockwise;
		rasterizer.depthBiasEnable = VK_FALSE;


		//multisampling
		vk::PipelineMultisampleStateCreateInfo multisampling = {};
		multisampling.sampleShadingEnable = VK_FALSE;
		multisampling.rasterizationSamples = vk::SampleCountFlagBits::e1;


		//color attachment
		vk::PipelineColorBlendAttachmentState colorBlendAttachment = {};
		colorBlendAttachment.colorWriteMask = vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA;
		colorBlendAttachment.blendEnable = VK_FALSE;


		vk::PipelineColorBlendStateCreateInfo colorBlending = {};
		colorBlending.logicOpEnable = VK_FALSE;
		colorBlending.logicOp = vk::LogicOp::eCopy;
		colorBlending.attachmentCount = 1;
		colorBlending.pAttachments = &colorBlendAttachment;
		colorBlending.blendConstants[0] = 0.0f;
		colorBlending.blendConstants[1] = 0.0f;
		colorBlending.blendConstants[2] = 0.0f;
		colorBlending.blendConstants[3] = 0.0f;

		vk::PipelineLayoutCreateInfo pipelineLayoutInfo = {};
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pushConstantRangeCount = 0;

		try {
			pipelineLayout = device.createPipelineLayout(pipelineLayoutInfo);
		}
		catch (vk::SystemError err) {
			PGE_CORE_ERROR("failed to create pipeline layout!");
		}

		vk::GraphicsPipelineCreateInfo pipelineInfo = {};
		pipelineInfo.stageCount = 2;
		pipelineInfo.pStages = shaderStages;
		pipelineInfo.pVertexInputState = &vertexInputInfo;
		pipelineInfo.pInputAssemblyState = &inputAssembly;
		pipelineInfo.pViewportState = &viewportState;
		pipelineInfo.pRasterizationState = &rasterizer;
		pipelineInfo.pMultisampleState = &multisampling;
		pipelineInfo.pColorBlendState = &colorBlending;
		pipelineInfo.layout = pipelineLayout;
		pipelineInfo.renderPass = renderPass;
		pipelineInfo.subpass = 0;
		pipelineInfo.basePipelineHandle = nullptr;

        try {
            graphicsPipeline = device.createGraphicsPipeline(nullptr, pipelineInfo).value;
        }
        catch (vk::SystemError err) {
            PGE_CORE_ERROR("failed to create graphics pipeline!");
        }

		//shader modules are just a handle to the compiled shader programs,
		//they can and should be destroyed after being used to create shader stages
		device.destroyShaderModule(vertShaderModule);
		device.destroyShaderModule(fragShaderModule);

	}

	void create_render_pass(vk::RenderPass& renderPass, vk::Device device, vk::Format swapChainImageFormat) {
		vk::AttachmentDescription colorAttachment = {};
		colorAttachment.format = swapChainImageFormat;
		colorAttachment.samples = vk::SampleCountFlagBits::e1;
		colorAttachment.loadOp = vk::AttachmentLoadOp::eClear;
		colorAttachment.storeOp = vk::AttachmentStoreOp::eStore;
		colorAttachment.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
		colorAttachment.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
		colorAttachment.initialLayout = vk::ImageLayout::eUndefined;
		colorAttachment.finalLayout = vk::ImageLayout::ePresentSrcKHR;

		vk::AttachmentReference colorAttachmentRef = {};
		colorAttachmentRef.attachment = 0;
		colorAttachmentRef.layout = vk::ImageLayout::eColorAttachmentOptimal;

		vk::SubpassDescription subpass = {};
		subpass.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &colorAttachmentRef;

		//this is here to prevent the subpasss to become active before the image is acquired and ready
		vk::SubpassDependency dependency = {};
		dependency.srcSubpass = VK_SUBPASS_EXTERNAL; //implicit subpass before render begin/after it ends
		dependency.dstSubpass = 0;//the rendering subpass
		dependency.srcStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
		//dependency.srcAccessMask = 0;
		dependency.dstStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
		dependency.dstAccessMask = vk::AccessFlagBits::eColorAttachmentRead | vk::AccessFlagBits::eColorAttachmentWrite;


		vk::RenderPassCreateInfo renderPassInfo = {};
		renderPassInfo.attachmentCount = 1;
		renderPassInfo.pAttachments = &colorAttachment;
		renderPassInfo.subpassCount = 1;
		renderPassInfo.pSubpasses = &subpass;
		renderPassInfo.dependencyCount = 1;
		renderPassInfo.pDependencies = &dependency;

		try
		{
			renderPass = device.createRenderPass(renderPassInfo);
			PGE_CORE_INFO("render pass created succesfully");
		}
		catch (vk::SystemError err)
		{
			PGE_CORE_ERROR("failed to create renderpass");
		}
	}
}