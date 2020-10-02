#include "window.h"
#include "render_engine.h"

int main()
{
	int window_x{ 128 }; // Test tex is 320 x 304
	int window_y{ 128 };

	Window main_window(window_x * 3, window_y * 3);
	RenderEngine renderer(window_x, window_y);

	while (main_window.open())
	{
		renderer.render(main_window.world_position());
		main_window.refresh();
	}

	return 0;
}