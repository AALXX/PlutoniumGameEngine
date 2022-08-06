#include "pphd.h"
#include "OpenGLRendererApi.h"

#include <glad/glad.h>
#include "..\IamGuiOpenGl\IamGuiOpengl.h"
#include <iostream>

namespace PGE_OPENGL {
	bool OpenGLRendererAPI::Init()
	{

		std::string vertexSource = R"(
			#version 330 core
		
			layout(location = 0) in vec3 a_Position;			

			out vec3 v_Position;

			void main() {
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSource = R"(
			#version 330 core
		
			layout(location = 0) out vec4 color;			

			in vec3 v_Position;
		
			void main() {
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		m_Shader.reset(new OpenGlShader(vertexSource, fragmentSource));

		return true;
	}
	void OpenGLRendererAPI::GetWindow(GLFWwindow* window, int windowWidth, int windowHeight)
	{
	}
	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}
	
	void OpenGLRendererAPI::DrawIndexed()
	{
		m_Shader->Bind();
		glBindVertexArray(m_VertexArray);
		glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::SubmitVertices(glm::mat3x3 &vertices)
	{
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);


		m_VertexBuffer.reset(new OpenGLVertexBuffer(vertices, sizeof(vertices)));

		OpenGLBufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},

		};


		uint32_t index = 0;
		for (const auto& element :layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
			index++;
		}

		//m_VertexBuffer->SetLayout();




		unsigned int indices[3] = {
			0, 1, 2
		};

		m_IndexBuffer.reset(new OpenGLIndexBuffer(indices, sizeof(indices) / sizeof(uint32_t)));
	}

	bool OpenGLRendererAPI::release()
	{
		return true;
	}
}
