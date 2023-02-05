#pragma once

#include "defines.h"

namespace s2d
{

	class Renderer
	{
	public:
		void set_viewport(u32 width, u32 height);

		void draw_rect(const Vec2f& textureCoordinates,
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
		
	};

}