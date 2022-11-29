#pragma once

//Core
#include "PlutoniumGameEngine/LogingSystem/Log.h"
#include "PlutoniumGameEngine/LayerSystem/Layer.h"
#include "PlutoniumGameEngine/Application.h"
#include "PlutoniumGameEngine/IamGui/IamGuiLayer.h"
#include "PlutoniumGameEngine/Core/Timestep/TimeStep.h"	


//*Input
#include "PlutoniumGameEngine/Input/Input.h"
#include "PlutoniumGameEngine/Input/KeyCodes.h"
#include "PlutoniumGameEngine/Input/MouseButtonCodes.h"

//*Graphics engine
#include "PlutoniumGameEngine/GraphicsEngine/GraphicsEngine.h"
#include "PlutoniumGameEngine/GraphicsEngine/Renderer/RenderCommand.h"
#include "PlutoniumGameEngine/GraphicsEngine/Buffer/Buffer.h"
#include "PlutoniumGameEngine/GraphicsEngine/Shaders/Shader.h"
#include "PlutoniumGameEngine/GraphicsEngine/Buffer/VertexArray.h"
#include "PlutoniumGameEngine/GraphicsEngine/Cameras/OrtographicCamera/OrtographicCamera.h"
#include <PlutoniumGameEngine/GraphicsEngine/Texture/Texture.h>



// ---Entry Point---------------------
#include "PlutoniumGameEngine/EntryPoint/EntryPoint.h"
// -----------------------------------