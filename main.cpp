#include "window.h"
#include "render_engine.h"

int main()
{
	int window_x{ 256 };
	int window_y{ 256 };
	int render_x{ 128 };
	int render_y{ 128 };

	TileRender::Window main_window(window_x, window_y);
	GLRender::RenderEngine renderer(render_x, render_y);

	while (main_window.open())
	{
		renderer.render(main_window.world_position());
		main_window.refresh();
	}

	return 0;
}