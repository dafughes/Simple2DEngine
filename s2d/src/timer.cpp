#include "timer.h"

namespace s2d
{
	Timer::Timer() : m_start(std::chrono::high_resolution_clock::now()) {}

	void Timer::reset()
	{
		m_start = std::chrono::high_resolution_clock::now();
	}

	f32 Timer::seconds() const
	{
		return std::chrono::duration<f32>(std::chrono::high_resolution_clock::now() - m_start).count();
	}
}