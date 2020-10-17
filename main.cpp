#include "window.h"
#include "render_engine.h"

int main()
{
	int window_x{ 200 };
	int window_y{ 200 };

	TileRender::Window main_window(window_x, window_y);
	GLRender::RenderEngine renderer(window_x, window_y);

	while (main_window.open())
	{
		renderer.render(main_window.world_position());
		main_window.processInput();
		main_window.refresh();
	}

	return 0;
}