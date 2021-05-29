#pragma once
#include <d3d11.h>
#include "../../../../../Core/Core.h"

namespace PGE {

	class DeviceContext;
	class PGE_API SwapChain
	{
	public:
		SwapChain();
		~SwapChain();

		bool Init(HWND hwnd, UINT Width, UINT Height);

		bool present(bool vsync);

		//*Release SwapChain
		bool Release();

	private:
		IDXGISwapChain* m_swap_chain;
		ID3D11RenderTargetView* m_render_target_view;
	private:
		friend class DeviceContext;
	};

}
