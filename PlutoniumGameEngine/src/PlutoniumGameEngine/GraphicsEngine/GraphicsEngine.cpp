#include "pphd.h"
#include "GraphicsEngine.h"
#include "Platofrm/VulkanApi/Instance/Instance.h"

namespace PGE {

	GraphicsEngine::GraphicsEngine()
	{
		makeInstance();
	}

	bool GraphicsEngine::init()
	{
		return true;
	}

	bool GraphicsEngine::release()
	{

		return true;
	}

	GraphicsEngine::~GraphicsEngine()
	{
	}

	GraphicsEngine* GraphicsEngine::get()
	{
		static GraphicsEngine engine;
		return &engine;
	}

	void GraphicsEngine::makeInstance()
	{
		instance = PGE_VULKAN::make_instance(isDebug, "Plutonium engine");
	}

}
