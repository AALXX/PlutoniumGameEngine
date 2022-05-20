#pragma once
#include <vulkan/vulkan.hpp>

#include "PlutoniumGameEngine/GraphicsEngine/Renderer/RendererApi.h"


namespace PGE_VULKAN {

	struct Vertex {
		glm::vec2 pos;
		glm::vec3 color;

		static vk::VertexInputBindingDescription getBindingDescription() {
			vk::VertexInputBindingDescription bindingDescription = {};
			bindingDescription.binding = 0;
			bindingDescription.stride = sizeof(Vertex);
			bindingDescription.inputRate = vk::VertexInputRate::eVertex;

			return bindingDescription;
		}

		static std::array<vk::VertexInputAttributeDescription, 2> getAttributeDescriptions() {
			std::array<vk::VertexInputAttributeDescription, 2> attributeDescriptions = {};
			attributeDescriptions[0].binding = 0;
			attributeDescriptions[0].location = 0;
			attributeDescriptions[0].format = vk::Format::eR32G32Sfloat;
			attributeDescriptions[0].offset = offsetof(Vertex, pos);

			attributeDescriptions[1].binding = 0;
			attributeDescriptions[1].location = 1;
			attributeDescriptions[1].format = vk::Format::eR32G32B32Sfloat;
			attributeDescriptions[1].offset = offsetof(Vertex, color);

			return attributeDescriptions;
		}
	};

	class VulkanRendererAPI : public PGE::RendererAPI {

	public:

		virtual bool Init() override;

		virtual void GetWindow(GLFWwindow* window, int windowWidth, int windowHeight) override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed() {};
		virtual void WindowResized(int width, int height) override;
		virtual void DrawFrame() override;

		bool isDebug = true;

		const std::vector<Vertex> vertices = {
			{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
			{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
			{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
		};

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

		vk::Device device{ nullptr };

		vk::Queue graphicsQueue{ nullptr };
		vk::Queue presentQueue{ nullptr };

		void makeDevice();
	private:
		//SwapChain
		vk::SwapchainKHR swapChain{ nullptr };
		std::vector<vk::Image> swapChainImages{ nullptr };
		vk::Format swapChainImageFormat;
		vk::Extent2D swapChainExtent;

		std::vector<vk::ImageView> swapChainImageViews;

		void createSwapChain();
		void cleanupSwapChain();
		void createImageViews();

	public:
		void recreateSwapChain();
	private:
		//Render pass

		vk::RenderPass renderPass;
		void createRenderPass();

	private:
		//GraphicsPipeline

		vk::PipelineLayout pipelineLayout;
		vk::Pipeline graphicsPipeline;

		void createGraphicsPipeline();
	private:
		//FrameBuffer
		std::vector<vk::Framebuffer> swapChainFrameBuffers;
		vk::CommandPool commandPool;
		std::vector<vk::CommandBuffer> commandBuffer;

		bool framebufferResized = false;


		void createFrameBuffers();
		void createCommandPool();
		void createCommandBuffer();
	private:
		//multi threaded rendering
		std::vector<vk::Semaphore> imageAvailableSemaphore;
		std::vector<vk::Semaphore> renderFinishedSemaphore;
		std::vector<vk::Fence> inFlightFences;
		size_t currentFrame = 0;
		int _maxFramesInFlight = 2; //number of frames worked on
		size_t _currentFrame;

		void createSyncObjects();
		void drawFrame();
	private:
		//vertex impl

		void createVertexBuffer();

		vk::Buffer vertexBuffer;
		vk::DeviceMemory vertexBufferMemory;


	};
}