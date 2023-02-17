#pragma once

#include "defines.h"
#include "vec.h"

#include <vector>

namespace s2d
{

	class Renderer
	{
	public:
		Renderer();

		void* data() const;

		void set_viewport(u32 width, u32 height);

		void clear(u32 color);

		void draw_rect(
			const Vec2f* rect,
			const Vec2f* textureCoordinates,
			const Vec2u& textureSize,
			const void* texture,
			const Vec2f& pos,
			const Vec2f& scale,
			f32 rotation,
			const Vec2f& cameraPos,
			f32 zoom,
			f32 cameraRotation);

	private:
		u32 m_width, m_height;
		std::vector<u32> m_data;
	};

}