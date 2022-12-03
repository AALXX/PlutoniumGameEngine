#pragma once
#include <PlutoniumGameEngine.h>

class Sandbox3D : public PGE::Layer
{
public:
	Sandbox3D();
	virtual ~Sandbox3D() = default;

	virtual void OnAttach() override;
	virtual void OnDeAttach() override;

	void OnUpdate(PGE::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(PGE::Event& event) override;
private:
	PGE::OrthographicCameraController m_CameraController;


	PGE::Ref<PGE::Shader> m_FlatColorShader;
	PGE::Ref<PGE::VertexArray> m_SquareVA;
	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };


};

	