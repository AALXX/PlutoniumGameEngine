#include "pphd.h"
#include "Buffer.h"

#include "PlutoniumGameEngine/GraphicsEngine/Renderer/RendererApi.h"


#include "Platofrm/OpenGlApi/Buffer/OpenGlBuffer.h"

namespace PGE {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:    PGE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGl:  return new PGE_OPENGL::OpenGLVertexBuffer(vertices, size);
		//case RendererAPI::Vulkan:  return new PGE_OPENGL::OpenGLVertexBuffer(vertices, size);
		}

		PGE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:    PGE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::OpenGl:  return new PGE_OPENGL::OpenGLIndexBuffer(indices, size);
		}

		PGE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}