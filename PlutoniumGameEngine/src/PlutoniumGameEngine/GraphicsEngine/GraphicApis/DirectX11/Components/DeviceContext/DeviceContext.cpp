#include "DeviceContext.h"
#include "../SwapChain/SwapChain.h"
#include "../../../../../LogingSystem/Log.h"

namespace PGE {
	DeviceContext::DeviceContext(ID3D11DeviceContext* device_context):m_device_context(device_context)
	{

	}

	DeviceContext::~DeviceContext(){}

	bool DeviceContext::Release()
	{

		PGE_CORE_INFO("Released Device Context");
		m_device_context->Release();
		delete this;
		return true;
	}

	bool DeviceContext::ClearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha)
	{
		FLOAT clear_color[] = {red, green, blue, alpha};
		m_device_context->ClearRenderTargetView(swap_chain->m_render_target_view, clear_color);

		return true;
	}
}