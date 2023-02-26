#include "renderer.h"
#include "mat.h"
#include "bmp.h"

#include <algorithm>
#include <iostream>
#include <vector>

namespace s2d
{
	

	// Transforming e.g. view space to screen space
	static Mat3f coordinate_transform(const AABB& src, const AABB& dst)
	{
		auto T0 = Mat3f::translation(-src.left, -src.top);
		auto S = Mat3f::scaling(dst.width() / src.width(), dst.height() / src.height());
		auto T1 = Mat3f::translation(dst.left, dst.top);

		return T1 * S * T0;
	}

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
		void* screen_data)
	{
		// Winding order: from top left clockwise
		Vec2f vertices[]{
			{rect.left, rect.top},
			{rect.right, rect.top},
			{rect.right, rect.bottom},
			{rect.left, rect.bottom},
		};

		const f32 aspect_ratio{ (f32)screen_width / (f32)screen_height };

		auto M = Mat3f::translation(pos) * Mat3f::rotation(rotation) * Mat3f::scaling(scale);
		auto V = Mat3f::scaling(camera_zoom, camera_zoom) * Mat3f::rotation(-camera_rotation) * Mat3f::translation(-camera_pos);
		auto S = coordinate_transform({ -aspect_ratio, aspect_ratio, 1, -1 }, { 0, (f32)screen_width, 0, (f32)screen_height });

		auto T = S * V * M;
		// Transform vertices
		for (int i = 0; i < 4; i++)
		{
			vertices[i] = T * vertices[i];
		}

		// Bounding box
		AABB bb{
			vertices[0].x,
			vertices[0].x,
			vertices[0].y,
			vertices[0].y
		};

		for (int i = 0; i < 4; i++)
		{
			bb.left = std::min(bb.left, vertices[i].x);
			bb.right = std::max(bb.right, vertices[i].x);
			bb.top = std::min(bb.top, vertices[i].y);
			bb.bottom = std::max(bb.bottom, vertices[i].y);
		}

		// Clip to screen
		bb.left = clamp(bb.left, 0, (f32)screen_width);
		bb.right = clamp(bb.right, 0, (f32)screen_width);
		bb.top = clamp(bb.top, 0, (f32)screen_height);
		bb.bottom = clamp(bb.bottom, 0, (f32)screen_height);

		auto tex_transform = coordinate_transform(texture_coordinates, rect);

		auto T2 = T * tex_transform;
		auto inverse_transform = T2.inverse();

		Vec2f horizontal_increment = inverse_transform * Vec2f(1, 0) - inverse_transform * Vec2f(0, 0);
		Vec2f vertical_increment = inverse_transform * Vec2f(0, 1) - inverse_transform * Vec2f(0, 0);

		Vec2f p0 = inverse_transform * Vec2f(bb.left, bb.top);

		f32 tex_min_x = std::min(texture_coordinates.left, texture_coordinates.right);
		f32 tex_max_x = std::max(texture_coordinates.left, texture_coordinates.right);
		f32 tex_min_y = std::min(texture_coordinates.top, texture_coordinates.bottom);
		f32 tex_max_y = std::max(texture_coordinates.top, texture_coordinates.bottom);

		int x0 = (int)bb.left;
		int x1 = (int)bb.right;
		int y0 = (int)bb.top;
		int y1 = (int)bb.bottom;

		for (int y = y0; y < y1; y++, p0 += vertical_increment)
		{
			Vec2f p = p0;
			for (int x = x0; x < x1; x++, p += horizontal_increment)
			{
				if (p.x >= tex_min_x && p.x <= tex_max_x && p.y >= tex_min_y && p.y <= tex_max_y)
				{
					// Sample texture
					f32 tex_x = p.x * (texture_width - 1);
					f32 tex_y = p.y * (texture_height - 1);

					int idx = (int)tex_x + (int)tex_y * texture_width;
					u32* texture = (u32*)texture_data;
					auto sample = texture[idx];

					u32* screen = (u32*)screen_data;
					screen[x + y * screen_width] = sample;
				}
			}
		}
	}

	bool simple_font_loaded = false;
	u64 font[94];
	int ascii_offset = 33;

	void load_simple_font(const char* file)
	{
		Pixelbuffer font_image = load_bmp(file);

		if (font_image.size() == 0)
		{
			return;
		}

		simple_font_loaded = true;

		int font_index = 0;
		for (int y = 0; y < font_image.height(); y += 8)
		{
			for (int x = 0; x < font_image.width(); x += 8)
			{
				u64 glyph = 0;
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						u32 color = font_image.get_pixel(x + j, y + i);

						if (color == 0xff000000)
						{
							glyph |= (u64)1 << (i * 8 + j);
						}
					}
				}
				font[font_index] = glyph;

				font_index++;
				if (font_index > 94) return;
			}
		}
	}

	void draw_debug_text(const char* text, int x, int y, Pixelbuffer& buffer)
	{
		const int text_length = strlen(text);

		const int text_height = 0;
		const int text_width = text_length * 8;

		for (int i = 0; i < text_length; i++)
		{
			auto c = text[i];

			auto glyph = font[c - ascii_offset];

			for (int yy = 0; yy < 8; yy++)
			{
				for (int xx = 0; xx < 8; xx++)
				{
					if ((glyph >> (xx + yy * 8)) & 1)
					{
						buffer.set_pixel(x + i * 8 + xx, y + yy, 0xffffffff);
					}
				}
			}
		}
	}
}


