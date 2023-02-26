#pragma once

#include "defines.h"

namespace s2d
{

	/*enum class MouseButton : u8
	{
		None,

		Left,
		Middle,
		Right
	};*/

	class Mouse
	{
	public:
		void clear();
		

		int x = 0, y = 0;
		bool left_button_pressed = false;
		bool left_button_released = false;
		bool left_button_down = false;
		f32 wheel_delta = 0;
	};

}