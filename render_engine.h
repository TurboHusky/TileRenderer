#pragma once

#include "gl_buffers.h"
#include "gl_texture.h"
#include "gl_shader.h"

class RenderEngine
{
private:
	unsigned int width{ 0u };
	unsigned int height{ 0u };
	glm::uvec2 screen_position_old{ glm::uvec2(0u, 0u) };
	GLuint ubo_binding_index{ 0 };

	VertexArray screen_mask;
	VertexArray full_screen;
	Texture tileset;
	Buffer tile_map;
	FrameBuffer frame_buffer;
	Program tile_shader{ "tile_shader.vert", "tile_shader.frag" };
	Program screen_shader{ "screen.vert", "screen.frag" };
public:
	RenderEngine(const unsigned int screen_width, const unsigned int screen_height);
	void render(const glm::uvec2 world_position);
};

