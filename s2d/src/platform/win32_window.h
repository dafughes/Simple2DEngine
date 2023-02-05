#include "../windowbase.h"

#define NOMINMAX
#include <Windows.h>

namespace s2d
{

	class Win32Window : public WindowBase
	{
	public:
		Win32Window();
		virtual ~Win32Window();

		virtual bool initialize(u32 width, u32 height, std::string title, u32 flags = 0) override;
		virtual bool terminate() override;

		virtual void show(bool show) override;
		virtual void process_events() override;
		virtual void draw(void* data) override;

		virtual void set_size(u32 width, u32 height) override;
		virtual void set_title(std::string title) override;

	private:
		static LRESULT CALLBACK main_window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
		LRESULT CALLBACK window_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	private:
		HWND m_handle;
		BITMAPINFO m_bmi;
	};

}
