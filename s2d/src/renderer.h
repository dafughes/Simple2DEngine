#pragma once

#include "defines.h"
#include "vec.h"
#include "s2dmath.h"

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

	class Renderer
	{
	public:
		Renderer();

		void* data() const;

		void set_viewport(u32 width, u32 height);

		void clear(u32 color);

		

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

	private:
		u32 m_width, m_height;
		std::vector<u32> m_data;
	};

}