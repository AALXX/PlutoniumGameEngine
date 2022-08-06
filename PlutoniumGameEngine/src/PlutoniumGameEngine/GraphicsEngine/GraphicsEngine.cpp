#include "pphd.h"
#include "GraphicsEngine.h"

namespace PGE {

	GraphicsEngine::GraphicsEngine()
	{
	}

	bool GraphicsEngine::init()
	{

		return RenderCommand::Init();
	}

	void GraphicsEngine::BeginScene()
	{

	}

	void GraphicsEngine::EndScene()
	{
	}

	void GraphicsEngine::Submit()
	{
		RenderCommand::DrawIndexed();
	}

	bool GraphicsEngine::release()
	{
		return RenderCommand::release();
	}

	GraphicsEngine::~GraphicsEngine()
	{
	}

	GraphicsEngine* GraphicsEngine::get()
	{
		static GraphicsEngine engine;
		return &engine;
	}

}
