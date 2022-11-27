#pragma once

#include "PlutoniumGameEngine/GraphicsEngine/Buffer/VertexArray.h"

namespace PGE_OPENGL {

	class OpenGLVertexArray : public PGE::VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<PGE::VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<PGE::IndexBuffer>& indexBuffer) override;

		virtual const std::vector<std::shared_ptr<PGE::VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		virtual const std::shared_ptr<PGE::IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
	private:
		uint32_t m_RendererID;
		std::vector<std::shared_ptr<PGE::VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<PGE::IndexBuffer> m_IndexBuffer;
	};
}