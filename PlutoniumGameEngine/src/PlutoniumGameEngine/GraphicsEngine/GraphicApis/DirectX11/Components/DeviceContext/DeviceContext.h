#pragma once
#include <d3d11.h>
#include "../../../../../Core/Core.h"

namespace PGE {

	class SwapChain;

	class DeviceContext
	{
	public:
		DeviceContext(ID3D11DeviceContext* device_context);
		~DeviceContext();

		bool Release();
		bool ClearRenderTargetColor(SwapChain* swap_chain, float red, float green, float blue, float alpha);
	private:
		ID3D11DeviceContext* m_device_context;
	};
}
