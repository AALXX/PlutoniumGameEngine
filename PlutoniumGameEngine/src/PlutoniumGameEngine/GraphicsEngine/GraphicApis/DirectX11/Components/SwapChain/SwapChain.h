#pragma once
#include <d3d11.h>
#include "../../../../../Core/Core.h"

namespace PGE {


	class  SwapChain
	{
	public:
		SwapChain();
		~SwapChain();

		bool Init(HWND hwnd, UINT Width, UINT Height);

		//*Release SwapChain
		bool Release();

	private:
		IDXGISwapChain* m_swap_chain;
	};

}
