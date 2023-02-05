#include "win32_window.h"

namespace s2d
{
	Win32Window::Win32Window() : WindowBase()
	{

	}

	Win32Window::~Win32Window()
	{

	}

	bool Win32Window::initialize(u32 width, u32 height, std::string title, u32 flags)
	{
		// Register window class
		WNDCLASS wc{};

		wc.lpfnWndProc = main_window_proc;
		wc.hInstance = GetModuleHandle(nullptr);
		wc.lpszClassName = TEXT("MyWindowClass");

		auto result = RegisterClass(&wc);
		// TODO: Assert result

		// Fill bitmap info
		m_bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		m_bmi.bmiHeader.biWidth = (LONG)width;
		m_bmi.bmiHeader.biHeight = -(LONG)height;		// Negative height for top-down
		m_bmi.bmiHeader.biBitCount = 32;
		m_bmi.bmiHeader.biPlanes = 1;
		m_bmi.bmiHeader.biCompression = BI_RGB;

		// Window style
		DWORD style = WS_OVERLAPPEDWINDOW;

		// Calculate window size to hold client size of (width, height)
		RECT r{};
		r.right = width;
		r.bottom = height;

		AdjustWindowRect(&r, style, FALSE);
		auto windowWidth = r.right - r.left;
		auto windowHeight = r.bottom - r.top;

		// Create window
		m_handle = CreateWindowEx(
			0,
			TEXT("MyWindowClass"),
			title.c_str(),
			style,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			windowWidth,
			windowHeight,
			0,
			0,
			GetModuleHandle(nullptr),
			(void*)this
		);

		// TODO: Assert window handle

		m_isOpen = true;

		return true;
	}

	bool Win32Window::terminate()
	{
		// Stuff
		return true;
	}

	void Win32Window::show(bool show)
	{
		int showCmd = show ? SW_SHOW : SW_HIDE;
		ShowWindow(m_handle, showCmd);
	}

	void Win32Window::process_events()
	{
		MSG msg{};
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void Win32Window::draw(void* data)
	{
		auto w = m_bmi.bmiHeader.biWidth;
		auto h = -m_bmi.bmiHeader.biHeight;		// bmiheader height is negative so flip

		HDC hdc = GetDC(m_handle);

		StretchDIBits(hdc, 0, 0, w, h, 0, 0, w, h, data, &m_bmi, DIB_RGB_COLORS, SRCCOPY);

		ReleaseDC(m_handle, hdc);
	}

	void Win32Window::set_size(u32 width, u32 height)
	{
		m_width = width;
		m_height = height;

		RECT r{};
		r.right = width;
		r.bottom = height;

		AdjustWindowRect(&r, GetWindowLongPtr(m_handle, GWL_STYLE), FALSE);
		auto windowWidth = r.right - r.left;
		auto windowHeight = r.bottom - r.top;
		SetWindowPos(m_handle, 0, 0, 0, windowWidth, windowHeight, SWP_NOMOVE);
	}

	void Win32Window::set_title(std::string title)
	{
		SetWindowText(m_handle, title.c_str());
	}

	LRESULT CALLBACK Win32Window::main_window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		LRESULT result = 0;

		if (msg == WM_NCCREATE)
		{
			SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)((CREATESTRUCT*)lparam)->lpCreateParams);
		}

		Win32Window* window = (Win32Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

		if (window)
		{
			result = window->window_proc(hwnd, msg, wparam, lparam);
		}
		else
		{
			result = DefWindowProc(hwnd, msg, wparam, lparam);
		}

		return result;
	}

	LRESULT CALLBACK Win32Window::window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		LRESULT result = 0;

		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			m_isOpen = false;
			break;
		case WM_SIZE:
		{
			auto width = LOWORD(lparam);
			auto height = HIWORD(lparam);

			m_bmi.bmiHeader.biWidth = width;
			m_bmi.bmiHeader.biHeight = -height;

			m_width = static_cast<u32>(width);
			m_height = static_cast<u32>(height);

		} break;
		default:
			result = DefWindowProc(hwnd, msg, wparam, lparam);
		}

		return result;
	}
}