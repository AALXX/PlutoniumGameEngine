#pragma once

#include "PlutoniumGameEngine/GraphicsEngine/Renderer/RendererApi.h"
#include "Platofrm/OpenGlApi/Shader/OpenGlShader.h"
#include <Platofrm/OpenGlApi/Buffer/OpenGlBuffer.h>

namespace PGE_OPENGL {
	class OpenGLRendererAPI : public PGE::RendererAPI {
	public:

		virtual bool Init() override;
		virtual void GetWindow(GLFWwindow* window, int width, int height) override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;
		virtual void DrawIndexed() override;
		virtual void SubmitVertices(glm::mat3x3 &vertices) override;

		virtual void WindowResized(int width, int height) {
			PGE_CORE_TRACE("{0}, {1}", width, height);
		};
		virtual bool release() override;

	private:
		//Vertex Array
		unsigned int m_VertexArray;
		std::unique_ptr<OpenGLVertexBuffer> m_VertexBuffer;
		std::unique_ptr<OpenGLIndexBuffer> m_IndexBuffer;


	private:
		//shader
		std::unique_ptr<OpenGlShader> m_Shader;
	};
}