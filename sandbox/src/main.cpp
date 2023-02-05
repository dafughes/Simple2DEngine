#include "window.h"
#include "renderer.h"

using namespace s2d;

int main()
{
	Window window;

	window.initialize(640, 480, "Game");
	window.show(true);

	while(window.is_open())
	{
		window.process_events();

		
	}

	window.terminate();
}