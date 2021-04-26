#pragma once
#include<d3d11.h>

namespace PGE {
	class GraphicsEngine
	{
	public:
		GraphicsEngine() {};
		~GraphicsEngine() {};

		//* initializate graphics engine
		bool Init();
		//* release graphics engine
		bool Release();

	public:

		static GraphicsEngine* get();

	private:
		ID3D11Device* m_d3d11_device;
		D3D_FEATURE_LEVEL m_feature_level;
		ID3D11DeviceContext* m_imm_device_context;
	};
}


