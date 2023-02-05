#include "renderer.h"

#include "mat.h"
#include "s2dmath.h"

namespace s2d
{
	void Renderer::set_viewport(u32 width, u32 height)
	{

	}

	void Renderer::draw_rect(
		const Vec2f& textureCoordinates,
		const Vec2u& textureSize,
		const void* texture,
		const Vec2f& pos,
		const Vec2f& scale,
		f32 rotation,
		const Vec2f& cameraPos,
		f32 zoom,
		f32 cameraRotation
	)
	{
		/*
		Input:
			- (implicit) 1x1 rect vertices as an AABB
			- rect texture coordinates
			- texture: size, data
			- rect transform: pos, scale, rotation
			- camera transform: pos, zoom, rotation
		*/

		Vec3f vertices[4];

		// Transform rect to view space ([-ar, 1], [ar, -1])
		// World transform
		//auto M = Mat3f::translation(pos.x, pos.y) * Mat3f::rotation(rotation) * Mat3f::scaling(scale.x, scale.y);

		// View transform
		//auto V = Mat3f::scaling(zoom, zoom) * Mat3f::rotation(camera_rotation) * Mat3f::translation(camera_pos.x, camera_pos.y);

		//auto T = V * M;
		
		for (int i = 0; i < 4; i++)
		{
			//vertices[i] = T * vertices[i];
		}

		// Get bounding box
		//Rect bb(vertices[0].xy(), vertices[1].xy(), vertices[2].xy(), vertices[3].xy());

		// Clip to screen
		const f32 aspectRatio = (f32)m_width / (f32)m_height;
		Rect clipRegion(-aspectRatio / 2, aspectRatio / 2, -1, 1);

		// If inside screen
		/*if (bb.clip(clipRegion))
		{

		}*/
		


	}
}


