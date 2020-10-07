#pragma once

#include "gl_buffer.h"
#include "gl_texture.h"
#include "gl_shader.h"
#include "gl_vertexarray.h"
#include "gl_framebuffer.h"

namespace GLRender
{
	class RenderEngine
	{
	private:
		unsigned int m_width{ 0u };
		unsigned int m_height{ 0u };
		glm::uvec2 m_screen_position_old{ glm::uvec2(0u, 0u) };
		GLuint m_ubo_binding_index{ 0 };

		VertexArray m_screen_mask;
		VertexArray m_full_screen;
		Texture m_tileset;
		Buffer m_tile_map{ GL_UNIFORM_BUFFER };
		FrameBuffer m_frame_buffer;
		Program m_tile_shader{ "tile_shader.vert", "tile_shader.frag" };
		Program m_screen_shader{ "screen.vert", "screen.frag" };
	public:
		RenderEngine(const unsigned int screen_width, const unsigned int screen_height);
		void render(const glm::uvec2 world_position);
	};
}