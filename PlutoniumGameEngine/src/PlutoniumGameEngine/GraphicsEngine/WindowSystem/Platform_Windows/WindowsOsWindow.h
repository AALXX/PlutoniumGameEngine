#pragma once
#include "../Window.h"
//* Graphics engine
#include "../../GraphicsEngine.h"

namespace PGE {


	class WindowsOsWindow : public Window
	{
	public:
		WindowsOsWindow(const WindowProps& props);
		virtual ~WindowsOsWindow();

		void OnCreate() override;
		void OnUpdate() override;
		void OnDestroy() override;


		inline unsigned int GetWidth() const override { return m_WndData.width;  };
		inline unsigned int GetHeight() const override { return m_WndData.height;};

		RECT getClientWindowRect() override;
		HWND GetHwnd() override;
		void SetHwnd(HWND hwnd);

		// Window attributes
		inline void SetEventCallback(const EventCallbackFunc& callback) override { EventCallback = callback; };
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;


	private:
		virtual void Init(const WindowProps& props);
		virtual void Release();

	private:
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

		struct WindowData {
			LPCSTR Title;
			unsigned int width, height;
			bool VSync;

		};
		EventCallbackFunc EventCallback;

		WindowData m_WndData;
		HWND m_hwnd;

		//*SwapChain
		SwapChain* m_swap_chain;
	};
}

