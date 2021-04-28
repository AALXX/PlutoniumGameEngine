#pragma once
#include<d3d11.h>
#include "../Core/Core.h"
#include "GraphicApis/DirectX11/Components/SwapChain/SwapChain.h"

class SwapChain;

namespace PGE {
	class GraphicsEngine
	{
	public:
		GraphicsEngine();
		~GraphicsEngine();

		//* initializate graphics engine
		bool Init();
		//* release graphics engine
		bool Release();
	public:
		SwapChain* createSwapChain();

	public:

		static GraphicsEngine* get();

	private:
		ID3D11Device* m_d3d11_device;
		D3D_FEATURE_LEVEL m_feature_level;
		ID3D11DeviceContext* m_imm_device_context;

	private:
		IDXGIDevice* m_dxgi_device;
		IDXGIAdapter* m_dxgi_adapter;
		IDXGIFactory* m_dxgi_factory;

	private:
		friend class SwapChain;
	};
}


