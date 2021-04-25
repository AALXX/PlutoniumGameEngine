#pragma once
#include <Windows.h>
#include <string>
#include "../../Core/Core.h"
#include "../../EventSystem/Event.h"
#include "../../EventSystem/AplicationEvent.h"
#include "../../EventSystem/KeyEvent.h"
#include "../../EventSystem/MouseEvent.h"

namespace PGE {

	struct WindowProps
	{
		LPCSTR Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const LPCSTR& title = "Plutonium Game Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	// Interface representing a desktop system based Window
	class PGE_API Window
	{
	public:
		using EventCallbackFunc = std::function<void(Event&)>;

		virtual ~Window() {}
		
		virtual void OnCreate(HWND hwnd) = 0;
		virtual void OnUpdate() = 0;
		virtual void OnDestroy(HWND hwnd) = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// Window attributes
		virtual void SetEventCallback(const EventCallbackFunc& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}