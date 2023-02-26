#pragma once

#include "defines.h"

#include <string>
#include "keyboard.h"
#include "mouse.h"

namespace s2d
{

	class WindowBase
	{
	public:
		WindowBase();
		virtual ~WindowBase();

		virtual bool initialize(u32 width, u32 height, std::string title, u32 flags = 0) = 0;
		virtual bool terminate() = 0;

		virtual bool is_open() const;
		
		virtual void show(bool show) = 0;
		virtual void process_events() = 0;
		virtual void draw(void* data) = 0;

		virtual u32 width() const;
		virtual u32 height() const;
		virtual std::string title() const;

		virtual void set_size(u32 width, u32 height) = 0;
		virtual void set_title(std::string title) = 0;

		virtual const Keyboard& keyboard() const;
		virtual const Mouse& mouse() const;

	protected:
		bool m_isOpen;
		u32 m_width, m_height;
		std::string m_title;

		Keyboard m_keyboard;
		Mouse m_mouse;
	};
	
}