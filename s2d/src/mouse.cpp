#include "mouse.h"

namespace s2d
{
	void Mouse::clear()
	{
		wheel_delta = 0;

		left_button_pressed = false;
		left_button_released = false;
	}

	
}