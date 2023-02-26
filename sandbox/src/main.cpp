#include "window.h"
#include "renderer.h"
#include "s2dmath.h"
#include "pixelbuffer.h"

#include <chrono>
#include <iostream>
#include "mat.h"
#include <timer.h>

using namespace s2d;





void draw_line(int x0, int x1, int y0, int y1, u32 color, Pixelbuffer& buffer)
{
	
	f32 dx = (f32)x1 - (f32)x0;
	f32 dy = (f32)y1 - (f32)y0;


	if (dx == 0)
	{
		if (y1 < y0) std::swap(y0, y1);
		int x = x0;
		for (int y = y0; y <= y1; y++) { buffer.set_pixel(x, y, color); }
	}
	else if (dy == 0)
	{
		if (x1 < x0) std::swap(x0, x1);
		int y = y0;
		for (int x = x0; x <= x1; x++) { buffer.set_pixel(x, y, color); }
	}
	else if (std::abs((f32)dy / (f32)dx) > 1)
	{
		if (y1 < y0)
		{
			std::swap(y0, y1);
			std::swap(x0, x1);
		}
		f32 incr = dx / dy;
		f32 x = x0;
		for (int y = y0; y <= y1; y++, x += incr) 
		{
			buffer.set_pixel((int)x, y, color);
		}
	}
	else
	{
		if (x1 < x0)
		{
			std::swap(y0, y1);
			std::swap(x0, x1);
		}
		f32 incr = dy / dx;
		f32 y = y0;
		for (int x = x0; x <= x1; x++, y += incr)
		{
			buffer.set_pixel(x, (int)y, color);
		}
	}

	
	
}



u32 rgb(f32 r, f32 g, f32 b)
{
	r = clamp(r, 0, 1);
	g = clamp(g, 0, 1);
	b = clamp(b, 0, 1);

	u32 red = static_cast<u32>(r * 255.0f);
	u32 green = static_cast<u32>(g * 255.0f);
	u32 blue = static_cast<u32>(b * 255.0f);

	return blue | (green << 8) | (red << 16) | 0xff000000;
}

int main()
{
	const int width = 640;
	const int height = 480;
	
	Pixelbuffer screenbuffer(width, height);

	AABB rect{ -1, 1, 0.5, -0.5 };
	AABB tex{ 0, 1, 1, 0 };

	Vec2f pos{ 0,0 };
	Vec2f scale{ 1,1 };
	f32 rotation{ to_radians(0) };

	Vec2f camera_pos{ 0,0 };
	f32 zoom{ 1 };
	f32 camera_rotation{ to_radians(0) };


	// Test sprite
	Pixelbuffer sprite(256, 256);

	for (int y = 0; y < sprite.height(); y++)
	{
		f32 red = (f32)y / (f32)sprite.height();


		

		for (int x = 0; x < sprite.width(); x++)
		{
			f32 blue = (f32)x / (f32)sprite.width();
			sprite.set_pixel(x, y, rgb(red, 0, blue));
		}
	}


	Window window;
	window.initialize(width, height, "Test");

	window.show(true);

	Timer timer;

	int drag_x = 0;
	int drag_y = 0;

	Vec2f prev_camera_pos;
	bool is_dragged = false;

	while (window.is_open())
	{
		window.process_events();

		auto dt = timer.seconds();
		timer.reset();

		const f32 velocity{ 1 };
		const f32 angular_velocity{ 1 };
		const f32 zoom_speed{ 0.1 };

		//std::cout << window.mouse().x << ", " << window.mouse().y << "\n";

		auto new_zoom = zoom + zoom_speed * window.mouse().wheel_delta;

		if (new_zoom <= 0.0f)
		{
			new_zoom = 0.00001f;
		}

		if (new_zoom != zoom)
		{
			std::cout << new_zoom << "\n";
		}
		zoom = new_zoom;
		
		// "Player" control
		if (window.keyboard().is_down(Keycode::W))
		{
			pos.y += velocity * dt;
		}
		else if (window.keyboard().is_down(Keycode::S))
		{
			pos.y -= velocity * dt;
		}

		if (window.keyboard().is_down(Keycode::A))
		{
			pos.x -= velocity * dt;
		}
		else if (window.keyboard().is_down(Keycode::D))
		{
			pos.x += velocity * dt;
		}

		if (window.keyboard().is_down(Keycode::E))
		{
			rotation -= angular_velocity * dt;
		}
		else if (window.keyboard().is_down(Keycode::Q))
		{
			rotation += angular_velocity * dt;
		}

		// Camera control
		if (window.keyboard().is_down(Keycode::NUMPAD_8))
		{
			camera_pos.y += velocity * dt;
		}
		else if (window.keyboard().is_down(Keycode::NUMPAD_2))
		{
			camera_pos.y -= velocity * dt;
		}

		if (window.keyboard().is_down(Keycode::NUMPAD_4))
		{
			camera_pos.x -= velocity * dt;
		}
		else if (window.keyboard().is_down(Keycode::NUMPAD_6))
		{
			camera_pos.x += velocity * dt;
		}

		if (window.keyboard().is_down(Keycode::NUMPAD_9))
		{
			camera_rotation -= angular_velocity * dt;
		}
		else if (window.keyboard().is_down(Keycode::NUMPAD_7))
		{
			camera_rotation += angular_velocity * dt;
		}

		if (window.mouse().left_button_pressed)
		{
			drag_x = window.mouse().x;
			drag_y = window.mouse().y;

			prev_camera_pos = camera_pos;
		}
		else if (window.mouse().left_button_down)
		{
			int drag_dx = window.mouse().x - drag_x;
			int drag_dy = window.mouse().y - drag_y;

			f32 dx = (f32)drag_dx / (f32)window.width();
			f32 dy = (f32)drag_dy / (f32)window.height();

			std::cout << dx << ", " << dy << "\n";

			camera_pos.x = prev_camera_pos.x - dx;
			camera_pos.y = prev_camera_pos.y + dy;
		}


		

		screenbuffer.clear(0);
		int w = window.width();
		int h = window.height();

		if (w != (int)screenbuffer.width() || h != (int)screenbuffer.height())
		{
			screenbuffer.resize(w, h);
		}
		

		draw_rect(rect, tex, pos, scale, rotation, camera_pos, zoom, camera_rotation,
			sprite.width(), sprite.height(), (const void*)sprite.data(),
			screenbuffer.width(), screenbuffer.height(), (void*)screenbuffer.data());

		window.draw(screenbuffer.data());
	}

	window.terminate();
}