#pragma once

#include "defines.h"
#include "vec.h"

namespace s2d
{
	constexpr f32 PI = 3.14159265359f;

	constexpr f32 to_radians(f32 degrees)
	{
		return PI * degrees / 180;
	}

	constexpr f32 to_degrees(f32 radians)
	{
		return 180 * radians / PI;
	}

	// Represents an AABB
	class Rect
	{
	public:
		Rect(f32 x0, f32 x1, f32 y0, f32 y1);
		Rect(const Vec2f& v0, const Vec2f& v1, const Vec2f& v2, const Vec2f& v3);

		bool clip(const Rect& other);

		f32 x0, x1, y0, y1;
	};


}