#include "win32_window.h"
#include <iostream>
#include <windowsx.h>

namespace s2d
{
	// Keycode conversion
	constexpr Keycode convert_keycode(WPARAM keycode)
	{
		switch (keycode)
		{
		case 0x41: return Keycode::A;
		case 0x44: return Keycode::D;
		case 0x45: return Keycode::E;
		case 0x51: return Keycode::Q;
		case 0x53: return Keycode::S;
		case 0x57: return Keycode::W;
		case VK_NUMPAD0: return Keycode::NUMPAD_0;
		case VK_NUMPAD1: return Keycode::NUMPAD_1;
		case VK_NUMPAD2: return Keycode::NUMPAD_2;
		case VK_NUMPAD3: return Keycode::NUMPAD_3;
		case VK_NUMPAD4: return Keycode::NUMPAD_4;
		case VK_NUMPAD5: return Keycode::NUMPAD_5;
		case VK_NUMPAD6: return Keycode::NUMPAD_6;
		case VK_NUMPAD7: return Keycode::NUMPAD_7;
		case VK_NUMPAD8: return Keycode::NUMPAD_8;
		case VK_NUMPAD9: return Keycode::NUMPAD_9;
		default: return Keycode::None;
		}
	}

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
		// Clear keypresses/releases
		m_keyboard.clear();

		// Clear mouse
		m_mouse.clear();

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
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		{
			m_keyboard.set_pressed(convert_keycode(wparam));
		} break;
		case WM_KEYUP:
		case WM_SYSKEYUP:
		{
			m_keyboard.set_released(convert_keycode(wparam));
		} break;
		case WM_MOUSEWHEEL:
		{
			auto delta = (f32)GET_WHEEL_DELTA_WPARAM(wparam) / (f32)WHEEL_DELTA;
			m_mouse.wheel_delta = delta;
		} break;
		case WM_MOUSEMOVE:
		{
			m_mouse.x = GET_X_LPARAM(lparam);
			m_mouse.y = GET_Y_LPARAM(lparam);
		} break;
		case WM_LBUTTONDOWN:
		{
			m_mouse.left_button_down = true;
			m_mouse.left_button_pressed = true;
		} break;
		case WM_LBUTTONUP:
		{
			m_mouse.left_button_down = false;
			m_mouse.left_button_released = true;
		} break;
		default:
			result = DefWindowProc(hwnd, msg, wparam, lparam);
		}

		return result;
	}
}