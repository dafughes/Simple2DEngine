#include "window.h"
#include "renderer.h"
#include "s2dmath.h"

#include <chrono>
#include <iostream>

using namespace s2d;

int main()
{
	Window window;

	Renderer renderer;
	renderer.set_viewport(640, 480);
	Vec2f vertices[]{
		{-0.5, 0.5},
		{0.5, 0.5},
		{0.5, -0.5},
		{-0.5, -0.5},
	};

	Vec2f texcoords[]{
		{0,0},
		{1,0},
		{1,1},
		{0,1},
	};

	Vec2u texsize{64,64};

	Vec2f pos{ 0,0 };
	Vec2f scale{ 1,1 };
	f32 rot{ to_radians(0)};

	Vec2f campos{ 0,0 };
	f32 zoom{ 1 };
	f32 camrot{ to_radians(0) };

	void* tex = nullptr;

	window.initialize(640, 480, "Game");
	window.show(true);

	const f32 rotvel = to_radians(15);

	auto t = std::chrono::high_resolution_clock::now();

	while(window.is_open())
	{
		window.process_events();

		renderer.clear(0);

		auto dt = std::chrono::duration<f32>(std::chrono::high_resolution_clock::now() - t).count();
		t = std::chrono::high_resolution_clock::now();
		std::cout << 1 / dt << "\n";
		rot += dt * rotvel;

		renderer.draw_rect(
			vertices,
			texcoords,
			texsize,
			tex,
			pos,
			scale,
			rot,
			campos,
			zoom,
			camrot
		);
		
		window.draw(renderer.data());

	}

	window.terminate();
}