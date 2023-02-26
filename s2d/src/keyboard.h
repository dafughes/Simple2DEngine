#pragma once

#include "defines.h"

#include <set>

namespace s2d
{

	enum class Keycode : u8
	{
		None,
		W,
		A,
		S,
		D,
		E,
		Q,

		NUMPAD_0,
		NUMPAD_1,
		NUMPAD_2,
		NUMPAD_3,
		NUMPAD_4,
		NUMPAD_5,
		NUMPAD_6,
		NUMPAD_7,
		NUMPAD_8,
		NUMPAD_9,
	};

	class Keyboard
	{
	public:
		void clear();
		void set_pressed(Keycode key);
		void set_released(Keycode key);

		bool is_down(Keycode key) const;
		bool is_pressed(Keycode key) const;
		bool is_released(Keycode key) const;


	private:
		std::set<Keycode> m_down, m_pressed, m_released;
	};

}