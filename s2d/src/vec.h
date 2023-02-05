#pragma once

#include "defines.h"

namespace s2d
{

	template <typename T>
	class Vec2
	{
	public:


		T x, y;
	};

	template <typename T>
	class Vec3
	{
	public:


		T x, y, z;
	};

	using Vec2f = Vec2<f32>;
	using Vec2u = Vec2<u32>;
	using Vec2i = Vec2<i32>;

	using Vec3f = Vec3<f32>;
	using Vec3u = Vec3<u32>;
	using Vec3i = Vec3<i32>;
}