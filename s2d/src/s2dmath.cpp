#include "s2dmath.h"

namespace s2d
{
	Rect::Rect(f32 x0, f32 x1, f32 y0, f32 y1) :
		x0(x0), x1(x1), y0(y0), y1(y1)
	{

	}

	Rect::Rect(const Vec2f& v0, const Vec2f& v1, const Vec2f& v2, const Vec2f& v3)
	{

	}

	bool Rect::clip(const Rect& other)
	{
		return true;
	}
}