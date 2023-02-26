#pragma once

#include "defines.h"
#include "vec.h"
#include "s2dmath.h"
#include "pixelbuffer.h"

#include <vector>

namespace s2d
{

	struct Transform
	{
		Vec2f position;
		Vec2f scale;
		f32 rotation;
	};

	void draw_rect(
		const AABB& rect,
		const AABB& texture_coordinates,
		const Vec2f& pos,
		const Vec2f& scale,
		f32 rotation,
		const Vec2f& camera_pos,
		f32 camera_zoom,
		f32 camera_rotation,
		int texture_width,
		int texture_height,
		const void* texture_data,
		int screen_width,
		int screen_height,
		void* screen_data);

	void load_simple_font(const char* file);

	void draw_debug_text(const char* text, int x, int y, Pixelbuffer& buffer);

}