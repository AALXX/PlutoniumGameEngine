#include "WindowsOsWindow.h"

#include "../../../LogingSystem/Log.h"
#include "../../../EventSystem/AplicationEvent.h"
#include "../../../EventSystem/MouseEvent.h"
#include "../../../EventSystem/KeyEvent.h"
#include <iostream>
#include <typeinfo>

namespace PGE {

	Window* Window::Create(const WindowProps& props) {
		return new WindowsOsWindow(props);
	}

	WindowsOsWindow::WindowsOsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsOsWindow::~WindowsOsWindow()
	{
		Release();
	}



	void WindowsOsWindow::SetVSync(bool enabled)
	{
	}

	bool WindowsOsWindow::IsVSync() const
	{
		return false;
	}


	LRESULT WindowsOsWindow::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		switch (msg)
		{

		case WM_CREATE:
		{
			// Event fired when the window is created
			WindowsOsWindow* window = (WindowsOsWindow*)((LPCREATESTRUCT)lparam)->lpCreateParams;
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);


			window->OnCreate(hwnd);

			break;
		}
		case WM_DESTROY:
		{
			// Event fired when the window is destroyed
			WindowsOsWindow* window = (WindowsOsWindow*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			window->OnDestroy(hwnd);

			//* When close Callback 
			WindowCloseEvent event;
			window->EventCallback(event);


			break;
		}
		default:
			return ::DefWindowProc(hwnd, msg, wparam, lparam);
		}

		return NULL;
	}

	void WindowsOsWindow::Init(const WindowProps& props)
	{
		m_WndData.Title = props.Title;
		m_WndData.height = props.Height;
		m_WndData.width = props.Height;

		//* WNDCLASSX Object
		WNDCLASSEX wndclss;
		wndclss.cbClsExtra = NULL;
		wndclss.cbSize = sizeof(WNDCLASSEX);
		wndclss.cbWndExtra = NULL;
		wndclss.hbrBackground = (HBRUSH)COLOR_WINDOW;
		wndclss.hCursor = LoadCursor(NULL, IDC_ICON);
		wndclss.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wndclss.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		wndclss.hInstance = NULL;
		wndclss.lpszClassName = "PlutoniumWindowClass";
		wndclss.lpszMenuName = "";
		wndclss.style = NULL;
		wndclss.lpfnWndProc = &WndProc;


		//* check the registration of class
		if (!::RegisterClassEx(&wndclss)) {
			std::cout << "failed register window class \n";
		}


		//Creation of the window
		m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "PlutoniumWindowClass", m_WndData.Title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 
			(int)props.Width, (int)props.Height,
			NULL, NULL, NULL, this);

		if (!m_hwnd) {
			std::cout << "create window class \n";
		}



		//* Show window
		::ShowWindow(m_hwnd, SW_SHOW);
		::UpdateWindow(m_hwnd);

	}

	void WindowsOsWindow::OnCreate(HWND hwnd)
	{

	}

	void WindowsOsWindow::OnUpdate()
	{
		MSG msg;
		while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage( &msg);

		}
	}
	
	void WindowsOsWindow::Release()
	{
		::DestroyWindow(m_hwnd);
	}




	void WindowsOsWindow::OnDestroy(HWND hwnd)
	{

	}
}