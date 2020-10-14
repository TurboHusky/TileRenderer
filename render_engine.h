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
		unsigned int m_width;
		unsigned int m_height;
		glm::uvec2 m_screen_position_old;
		GLuint m_uniform_binding_point;

		VertexArray m_verts_bg;
		VertexArray m_verts_screen;
		Texture m_tex_tileset;
		Buffer m_buff_uniform_data;
		BufferTexture m_buff_tex_tile_indices; // No storage buffers in 3.3, use buffer texture
		FrameBuffer m_frame_buffer;
		Program m_tile_shader;
		Program m_screen_shader;
	public:
		RenderEngine(const unsigned int screen_width, const unsigned int screen_height);
		void render(const glm::uvec2 world_position);
	};
}