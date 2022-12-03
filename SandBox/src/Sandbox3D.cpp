#include "Sandbox3D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <Platofrm/OpenGlApi/OpenGLShader/OpenGLShader.h>
#include <glm/gtc/type_ptr.hpp>

Sandbox3D::Sandbox3D():
	Layer("Sandbox3D"),  m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox3D::OnAttach()
{
	m_SquareVA = PGE::VertexArray::Create();


	float squareVertices[5 * 4] = {
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


	m_FlatColorShader = PGE::Shader::Create("assets/shaders/FlatColorShader.glsl");
}

void Sandbox3D::OnDeAttach()
{

}

void Sandbox3D::OnUpdate(PGE::Timestep ts)
{
	//Update
	m_CameraController.OnUpdate(ts);

	//Renderer
	PGE::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	PGE::RenderCommand::Clear();

	PGE::GraphicsEngine::BeginScene(m_CameraController.GetCamera());


	std::dynamic_pointer_cast<PGE_OPENGL::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<PGE_OPENGL::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	PGE::GraphicsEngine::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	PGE::GraphicsEngine::EndScene();
}

void Sandbox3D::OnImGuiRender()
{
	ImGui::Begin("Settings");


	ImGui::ColorEdit4("Square color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void Sandbox3D::OnEvent(PGE::Event& event)
{
	m_CameraController.OnEvent(event);
}
