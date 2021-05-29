#pragma once
#include<d3d11.h>
#include "../Core/Core.h"
#include "GraphicApis/DirectX11/Components/SwapChain/SwapChain.h"
#include "GraphicApis/DirectX11/Components/DeviceContext/DeviceContext.h"

namespace PGE {
	class SwapChain;
	class DeviceContext;

	class PGE_API GraphicsEngine
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
		DeviceContext* getImmediateDeviceContext();
	public:

		static GraphicsEngine* get();
	private:
		DeviceContext* m_imm_device_context;

	private:
		ID3D11Device* m_d3d11_device;
		D3D_FEATURE_LEVEL m_feature_level;

	private:
		IDXGIDevice* m_dxgi_device;
		IDXGIAdapter* m_dxgi_adapter;
		IDXGIFactory* m_dxgi_factory;

	private:
		friend class SwapChain;
		friend class DeviceContext;
	};
}


