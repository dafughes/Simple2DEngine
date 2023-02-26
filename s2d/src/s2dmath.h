#pragma once

#include "defines.h"
#include "vec.h"
#include "mat.h"

#include <algorithm>

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

	constexpr f32 clamp(f32 value, f32 min = 0.0f, f32 max = 1.0f)
	{
		return std::max(std::min(value, max), min);
	}

	

	// Represents 4 arbitrarily rotated vertices
	struct Quad
	{

		Vec2f vertices[4];
	};
	
	struct AABB
	{
		f32 left, right, top, bottom;

		inline f32 width() const
		{
			return right - left;
		}

		inline f32 height() const
		{
			return top - bottom;
		}



		
	};

	

}