#pragma once

#include "gl_buffers.h"
#include "gl_texture.h"
#include "gl_shader.h"

class RenderEngine
{
private:
	unsigned int screen_width{ 0u };
	unsigned int screen_height{ 0u };
	glm::uvec2 screen_position_old{ glm::uvec2(0u, 0u) };

	VertexArray screen_mask;
	VertexArray full_screen;
	FrameBuffer frame_buffer;
	Buffer tile_map;
	Texture tileset;
	Program tile_shader{ "tile_shader.vert", "tile_shader.frag" };
	Program screen_shader{ "screen.vert", "screen.frag" };
public:
	RenderEngine(const unsigned int width, const unsigned int height);
	void render(const glm::uvec2 world_position);
};

