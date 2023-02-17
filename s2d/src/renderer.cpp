#include "renderer.h"
#include "mat.h"
#include "s2dmath.h"

#include <algorithm>
#include <iostream>
#include <vector>

namespace s2d
{
	Renderer::Renderer() : m_width(0), m_height(0), m_data(std::vector<u32>())
	{
	}
	void* Renderer::data() const
	{
		return (void*)m_data.data();
	}

	void Renderer::set_viewport(u32 width, u32 height)
	{
		m_width = width;
		m_height = height;
		m_data.resize(width * height);
	}

	void Renderer::clear(u32 color)
	{
		std::fill(m_data.begin(), m_data.end(), color);
	}

	void Renderer::draw_rect(
		const Vec2f* rect,
		const Vec2f* textureCoordinates,
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
		const f32 ar = (f32)m_width / m_height;
		Vec3f vertices[]{
			{rect[0].x, rect[0].y, 1},
			{rect[1].x, rect[1].y, 1},
			{rect[2].x, rect[2].y, 1},
			{rect[3].x, rect[3].y, 1},
		};

		// rect -> world -> view space
		// M = translate * rotation * scale
		// V = scale  * rotate * translate
		// S = translate * scale
		auto M =
			Mat3f::translation(pos.x, pos.y) *
			Mat3f::rotation(rotation) *
			Mat3f::scaling(scale.x, scale.y);
		auto V =
			Mat3f::scaling(zoom, zoom) *
			Mat3f::rotation(-cameraRotation) *
			Mat3f::translation(-cameraPos.x, -cameraPos.y);
		auto S =
			Mat3f::translation((f32)m_width / 2, (f32)m_height / 2.0f) *
			Mat3f::scaling((f32)m_width / (2 * ar), -(f32)m_height / 2.0f);
		auto MVS = S * V * M;

		for (int i = 0; i < 4; i++)
		{
			vertices[i] = M * vertices[i];
			vertices[i] = V * vertices[i];
			vertices[i] = S * vertices[i];
		}

		// Bounding box
		f32 left = vertices[0].x, right = vertices[0].x, top = vertices[0].y, bottom = vertices[0].y;

		for (int i = 0; i < 4; i++)
		{
			left = std::min(left, vertices[i].x);
			right = std::max(right, vertices[i].x);
			top = std::min(top, vertices[i].y);
			bottom = std::max(bottom, vertices[i].y);
		}

		// Cull/Clip
		f32 w = m_width;
		f32 h = m_height;

		left = std::max(std::min(left, w), 0.0f);
		right = std::min(std::max(right, 0.0f), w);
		top = std::max(std::min(top, h), 0.0f);
		bottom = std::min(std::max(bottom, 0.0f), h);

		if ((right - left) == 0 || (top - bottom) == 0)
		{
			return;
		}
		
		// texture to model transform
		f32 textureCoordsWidth = textureCoordinates[0].x;
		f32 textureCoordsHeight = textureCoordinates[0].y;

		f32 modelMinX = rect[0].x;
		f32 modelMaxX = rect[0].x;
		f32 modelMinY = rect[0].y;
		f32 modelMaxY = rect[0].y;

		for (int i = 0; i < 4; i++)
		{
			textureCoordsWidth = std::max(textureCoordsWidth, textureCoordinates[i].x);
			textureCoordsHeight = std::max(textureCoordsHeight, textureCoordinates[i].y);

			modelMinX = std::min(modelMinX, rect[i].x);
			modelMaxX = std::max(modelMaxX, rect[i].x);
			modelMinY = std::min(modelMinY, rect[i].y);
			modelMaxY = std::max(modelMaxY, rect[i].y);
		}

		f32 modelWidth = std::abs(modelMaxX - modelMinX);
		f32 modelHeight = std::abs(modelMaxY - modelMinY);

		auto TexToModel =
			Mat3f::translation(modelMinX, -modelMinY) *
			Mat3f::scaling(modelWidth / textureCoordsWidth, -modelHeight / textureCoordsHeight);

		auto screenToTexture = (MVS * TexToModel).inverse();

		Vec3f topLeft = { left, top, 1 };

		auto texIncrX = (screenToTexture * Vec3f(left + 1, top, 1)) - (screenToTexture * topLeft);
		auto texIncrY = (screenToTexture * Vec3f(left, top + 1, 1)) - (screenToTexture * topLeft);

		Vec3f t = screenToTexture * topLeft;

		std::vector<u32> tex(64 * 64);

		for (int i = 0; i < 64; i++)
		{
			u32 b = (u32)(255.0f * ((f32)i / 64));
			u32 color = b | (b << 8) | (b << 16) | 255 << 24;
			for (int j = 0; j < 64; j++)
			{
				tex[i * 64 + j] = color;
			}
		}


		for (int y = (int)top; y < (int)bottom; y++)
		{
			Vec3f p = t;
			for (int x = (int)left; x < (int)right; x++)
			{
				// Shitty texture sampling
				if (p.x >= 0 && p.y >= 0)
				{
					f32 x_ = p.x;
					f32 y_ = p.y;
					while (x_ >= 1)
					{
						x_ -= 1;
					}
					while (y_ >= 1)
					{
						y_ -= 1;
					}

					auto coord = (int)(x_ * 64) + (int)(y_ * 64 + 64);
					auto color = tex[coord];

					m_data[x + y * m_width] = color;
				}
				
				
				p += texIncrX;
			}
			t += texIncrY;
		}
	}
}


