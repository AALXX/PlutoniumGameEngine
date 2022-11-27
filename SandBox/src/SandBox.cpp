#include <PlutoniumGameEngine.h>

#include "imgui/imgui.h"

class TestLayer :public PGE::Layer
{
public:
	TestLayer() :Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) {
		m_VertexArray.reset(PGE::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<PGE::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(PGE::VertexBuffer::Create(vertices, sizeof(vertices)));
		PGE::BufferLayout layout = {
			{ PGE::ShaderDataType::Float3, "a_Position" },
			{ PGE::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<PGE::IndexBuffer> indexBuffer;
		indexBuffer.reset(PGE::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(PGE::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<PGE::VertexBuffer> squareVB;
		squareVB.reset(PGE::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ PGE::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<PGE::IndexBuffer> squareIB;
		squareIB.reset(PGE::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
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

		m_Shader.reset(new PGE::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new PGE::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate() override {
		PGE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		PGE::RenderCommand::Clear();

		m_Camera.SetRotation(45.0f);

		PGE::GraphicsEngine::BeginScene(m_Camera);

		PGE::GraphicsEngine::Submit(m_BlueShader, m_SquareVA);

		PGE::GraphicsEngine::Submit(m_Shader, m_VertexArray);

		PGE::GraphicsEngine::EndScene();
	}

	void OnEvent(PGE::Event& event) override {

	}

	virtual void OnImGuiRender() override {

	}
private:

	std::shared_ptr<PGE::Shader> m_Shader;
	std::shared_ptr<PGE::VertexArray> m_VertexArray;

	std::shared_ptr<PGE::Shader> m_BlueShader;
	std::shared_ptr<PGE::VertexArray> m_SquareVA;

	PGE::OrthographicCamera m_Camera;
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