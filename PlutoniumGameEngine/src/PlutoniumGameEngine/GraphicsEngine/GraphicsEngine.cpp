#include "GraphicsEngine.h"
#include "../LogingSystem/Log.h"

namespace PGE {

	bool GraphicsEngine::Init()
	{

		D3D_DRIVER_TYPE driver_types[] = {
			D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE_WARP,
			D3D_DRIVER_TYPE_REFERENCE,
		};

		UINT num_driver_types = ARRAYSIZE(driver_types);

		D3D_FEATURE_LEVEL feature_levels[] = {

			D3D_FEATURE_LEVEL_11_0

		};

		UINT num_feature_levels = ARRAYSIZE(feature_levels);

		HRESULT res = 0;

		for (UINT driver_types_index = 0; driver_types_index < num_driver_types;)
		{
			res =  D3D11CreateDevice(NULL, driver_types[driver_types_index], NULL, NULL, feature_levels, 
				num_feature_levels, D3D11_SDK_VERSION, &m_d3d11_device, &m_feature_level, &m_imm_device_context);

			if (SUCCEEDED(res)) {
				PGE_CORE_INFO("DirectX initializated succesfully");
				break;
			}

			driver_types_index++;
		}

		if (FAILED(res)) {
			PGE_CORE_ERROR("Couldn't initializate DirectX ");
			return false;
		}


		return true;
	}

	bool GraphicsEngine::Release()
	{
		m_imm_device_context->Release();
		m_d3d11_device->Release();
		PGE_CORE_INFO("DirectX released succesfully");

		return true;
	}

	GraphicsEngine* GraphicsEngine::get()
	{
		static GraphicsEngine engine;
		return &engine;
	}
}