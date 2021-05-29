#include "SwapChain.h"
#include "../../../../GraphicsEngine.h"
#include "../../../../../LogingSystem/Log.h"

namespace PGE {
	SwapChain::SwapChain()
	{
	}

	SwapChain::~SwapChain()
	{
	}

	bool SwapChain::Init(HWND hwnd, UINT Width, UINT Height)
	{

		ID3D11Device* device = GraphicsEngine::get()->m_d3d11_device;

		DXGI_SWAP_CHAIN_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.BufferCount = 1;
		desc.BufferDesc.Width = Width;
		desc.BufferDesc.Height = Height;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.RefreshRate.Numerator = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.OutputWindow = hwnd;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.Windowed = TRUE;


		//*Create swap chain for window woth indicate hwnd
		HRESULT  hr = GraphicsEngine::get()->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swap_chain);

		if (FAILED(hr)) {

			PGE_CORE_ERROR("failed create swap chain");

			return false;
		}
		PGE_CORE_INFO("created swap chain");
		
		//*Get back buffer 
		ID3D11Texture2D* buffer = NULL;
		hr = m_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&buffer);

		if (FAILED(hr)) {

			PGE_CORE_ERROR("failed to get back buffer");

			return false;
		}

		hr = device->CreateRenderTargetView(buffer, NULL, &m_render_target_view);
		buffer->Release();
		 

		if (FAILED(hr)) {

			PGE_CORE_ERROR("failed to create render target view");

			return false;
		}
		return true;
	}

	bool SwapChain::present(bool vsync)
	{
		m_swap_chain->Present(vsync, NULL);
		return true;
	}


	bool SwapChain::Release()
	{
		PGE_CORE_INFO("Released swap chain");

		m_swap_chain->Release();
		delete this;
		return true;
	}
}