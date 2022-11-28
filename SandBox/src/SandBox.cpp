#include <PlutoniumGameEngine.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Platofrm/OpenGlApi/OpenGLShader/OpenGLShader.h>
#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"

class TestLayer :public PGE::Layer
{
public:
	TestLayer() :Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f) {
		m_VertexArray.reset(PGE::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		PGE::Ref<PGE::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(PGE::VertexBuffer::Create(vertices, sizeof(vertices)));
		PGE::BufferLayout layout = {
			{ PGE::ShaderDataType::Float3, "a_Position" },
			{ PGE::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		PGE::Ref<PGE::IndexBuffer> indexBuffer;
		indexBuffer.reset(PGE::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(PGE::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		PGE::Ref<PGE::VertexBuffer> squareVB;
		squareVB.reset(PGE::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ PGE::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		PGE::Ref<PGE::IndexBuffer> squareIB;
		squareIB.reset(PGE::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_ModelMatrix;

			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_ModelMatrix * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(PGE::Shader::Create(vertexSrc, fragmentSrc));

		std::string flatColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_ModelMatrix;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_ModelMatrix * vec4(a_Position, 1.0);	
			}
		)";

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_FlatColorShader.reset(PGE::Shader::Create(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));
	}

	void OnUpdate(PGE::Timestep ts) override {

		if (PGE::Input::IsKeyPressed(PGE_KEY_A))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (PGE::Input::IsKeyPressed(PGE_KEY_D))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		if (PGE::Input::IsKeyPressed(PGE_KEY_W))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (PGE::Input::IsKeyPressed(PGE_KEY_S))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		if (PGE::Input::IsKeyPressed(PGE_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (PGE::Input::IsKeyPressed(PGE_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * ts;


		PGE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		PGE::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		PGE::GraphicsEngine::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<PGE_OPENGL::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<PGE_OPENGL::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;

				PGE::GraphicsEngine::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		PGE::GraphicsEngine::Submit(m_Shader, m_VertexArray);


		PGE::GraphicsEngine::EndScene();
	}

	void OnEvent(PGE::Event& event) override {

	}


	virtual void OnImGuiRender() override {
		ImGui::Begin("Settings");
		

		ImGui::ColorEdit3("Square color", glm::value_ptr(m_SquareColor));

		ImGui::End();

	}

private:

	PGE::Ref<PGE::Shader> m_Shader;
	PGE::Ref<PGE::VertexArray> m_VertexArray;

	PGE::Ref<PGE::Shader> m_FlatColorShader;
	PGE::Ref<PGE::VertexArray> m_SquareVA;

	PGE::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

};

class Sandbox : public PGE::Application
{
public:
	Sandbox()
	{
		PushLayer(new TestLayer());
	}

	~Sandbox()
	{

	}

};

PGE::Application* PGE::CreateApplication()
{
	return new Sandbox();
}