#include "pphd.h"
#include "IamGuiLayer.h"

#include "Platofrm/OpenGlApi/IamGuiOpenGl/IamGuiOpengl.h"

namespace PGE {


	ImGuiLayer::ImGuiLayer()
		: Layer("IamGuiLayer")
	{
		m_iamgui_renderer = new PGE_OPENGL::IamGuiOpenGlRenderer;
		//m_iamgui_renderer = new PGE_VULKAN::IamGuiVulkanRenderer;

	}

	ImGuiLayer::~ImGuiLayer()
	{
	}


	void ImGuiLayer::Begin()
	{
		m_iamgui_renderer->Begin();

	}

	void ImGuiLayer::End()
	{
		m_iamgui_renderer->End();

	}


	void ImGuiLayer::OnAttach()
	{
		m_iamgui_renderer->OnAttach();
	}

	void ImGuiLayer::OnDeAttach()
	{
		m_iamgui_renderer->OnDettach();

	}

	void ImGuiLayer::OnImGuiRender()
	{
		m_iamgui_renderer->OnImGuiRender() ;

	}

}