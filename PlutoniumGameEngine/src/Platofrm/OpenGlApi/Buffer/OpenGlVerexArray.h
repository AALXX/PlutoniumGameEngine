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

		virtual void AddVertexBuffer(const PGE::Ref<PGE::VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const PGE::Ref<PGE::IndexBuffer>& indexBuffer) override;

		virtual const std::vector<PGE::Ref<PGE::VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		virtual const PGE::Ref<PGE::IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
	private:
		uint32_t m_RendererID;
		std::vector<PGE::Ref<PGE::VertexBuffer>> m_VertexBuffers;
		PGE::Ref<PGE::IndexBuffer> m_IndexBuffer;
	};
}