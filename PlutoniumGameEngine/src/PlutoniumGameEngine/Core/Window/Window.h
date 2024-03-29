#pragma once
#include "pphd.h"
#include "PlutoniumGameEngine/Core/Core.h"
#include "PlutoniumGameEngine/EventSystem/Event.h"

namespace PGE {
	struct WindowProps
	{
		std::string windowTitle;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Plutonium Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: windowTitle(title), Width(width), Height(height)
		{
		}
	};

	// Interface representing a desktop system based Window
	class PGE_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;


		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0; //return window (glfw/win32 for example)

		static Window* Create(const WindowProps& props = WindowProps());
	};

}