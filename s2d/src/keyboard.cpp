#include "keyboard.h"

namespace s2d
{

	void Keyboard::clear()
	{
		m_pressed.clear();
		m_released.clear();
	}

	void Keyboard::set_pressed(Keycode key)
	{
		m_pressed.insert(key);
		m_down.insert(key);
	}

	void Keyboard::set_released(Keycode key)
	{
		m_released.erase(key);
		m_down.erase(key);
	}
		 
	bool Keyboard::is_down(Keycode key) const
	{
		return m_down.find(key) != m_down.end();
	}

	bool Keyboard::is_pressed(Keycode key) const
	{
		return m_pressed.find(key) != m_pressed.end();
	}

	bool Keyboard::is_released(Keycode key) const
	{
		return m_released.find(key) != m_released.end();
	}

}