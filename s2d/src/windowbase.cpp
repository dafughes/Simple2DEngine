#include "windowbase.h"

namespace s2d
{
	WindowBase::WindowBase() :
		m_isOpen(false),
		m_width(0),
		m_height(0),
		m_title()
	{

	}

	WindowBase::~WindowBase()
	{

	}

	bool WindowBase::is_open() const
	{
		return m_isOpen;
	}

	u32 WindowBase::width() const
	{
		return m_width;
	}

	u32 WindowBase::height() const
	{
		return m_height;
	}

	std::string WindowBase::title() const
	{
		return m_title;
	}

	const Keyboard& WindowBase::keyboard() const
	{
		return m_keyboard;
	}

	const Mouse& WindowBase::mouse() const
	{
		return m_mouse;
	}
	
}