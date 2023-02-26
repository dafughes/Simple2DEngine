#pragma once

#include "defines.h"

#include <chrono>

namespace s2d
{

	class Timer
	{
	public:
		Timer();

		void reset();

		f32 seconds() const;

	private:
		std::chrono::high_resolution_clock::time_point m_start;
	};

}