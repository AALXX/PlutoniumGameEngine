#pragma once
#include <Glad/glad.h>
#include <glm/glm.hpp>
#include "PlutoniumGameEngine/GraphicsEngine/Buffer/Buffer.h"

namespace PGE_OPENGL {

	class OpenGLVertexBuffer : public PGE::VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const PGE::BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const PGE::BufferLayout& layout) override { m_Layout = layout; }
	private:
		uint32_t m_RendererID;
		PGE::BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public PGE::IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual uint32_t GetCount() const { return m_Count; }
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}