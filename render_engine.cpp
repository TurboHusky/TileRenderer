#include "render_engine.h"
#include <array>

namespace GLRender
{
	RenderEngine::RenderEngine(const unsigned int screen_width, const unsigned int screen_height) :
		m_width{ screen_width },
		m_height{ screen_height },
		m_screen_position_old{ glm::uvec2(screen_width, screen_height) },
		m_ubo_binding_index{ 0 },
		// m_screen_mask{ ??? },
		// m_full_screen{ ??? },
		m_tileset{ "resources/38056.png", { Texture::ColourMode::rgba, Texture::Wrap::clamp, Texture::Wrap::clamp, Texture::Filter::nearest, Texture::Filter::nearest } },
		m_tile_map{ GL_UNIFORM_BUFFER },
		m_frame_buffer{ screen_width, screen_height, Texture::ColourMode::rgba },
		m_tile_shader{ "tile_shader.vert", "tile_shader.frag" },
		m_screen_shader{ "screen.vert", "screen.frag" }
	{
		std::array<float, 16> screen_verts{
			// position			// UV
			 1.0f,  1.0f,		1.0f, 1.0f,		// top right
			 1.0f, -1.0f,		1.0f, 0.0f,		// bottom right
			-1.0f, -1.0f,		0.0f, 0.0f,		// bottom left
			-1.0f,  1.0f,		0.0f, 1.0f		// top left
		};

		std::array<unsigned int, 6> screen_indices{
			0, 1, 3,
			1, 2, 3
		};

		std::vector<VertexAttribute> screen_attributes
		{
			VertexAttribute { 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0 },
			VertexAttribute { 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)) }
		};

		std::array<unsigned int, 72> bg_verts{
			// l, r, const				// b, t, const
			 0u,  1u,  0u,				0u,  0u,  screen_height,
			 0u,  1u,  0u,				0u,  1u,  0u,
			 1u,  0u,  0u,				0u,  1u,  0u,
			 1u,  0u,  0u,				0u,  0u,  screen_height,

			 0u,  0u,  screen_width,	0u,  1u,  0u,
			 0u,  0u,  screen_width,	1u,  0u,  0u,
			 0u,  0u,  0u,				1u,  0u,  0u,
			 0u,  0u,  0u,				0u,  1u,  0u,

			 0u,  1u,  0u,				1u,  0u,  0u,
			 0u,  1u,  0u,				0u,  0u,  0u,
			 1u,  0u,  0u,				0u,  0u,  0u,
			 1u,  0u,  0u,				1u,  0u,  0u
		};

		std::array<unsigned int, 18> bg_indices{
			0, 1, 3,
			1, 2, 3,
			4, 5, 7,
			5, 6, 7,
			8, 9, 11,
			9, 10, 11
		};

		std::vector<VertexAttribute> bg_attributes
		{
			VertexAttribute{ 3, GL_UNSIGNED_INT, GL_FALSE, 6 * sizeof(unsigned int), (void*)0 },
			VertexAttribute{ 3, GL_UNSIGNED_INT, GL_FALSE, 6 * sizeof(unsigned int), (void*)(3 * sizeof(unsigned int)) }
		};

		// Test code, copies tilemap image
		std::array<glm::uvec2, 380> tileset_indices;
		for (auto j = 0; j < 304 / 16; j++)
		{
			for (auto i = 0; i < 320 / 16; i++)
			{
				tileset_indices[i + 20 * j] = glm::uvec2(i * 16u, j * 16u);
			}
		}

		m_screen_vao.load(screen_verts, screen_indices, screen_attributes);
		m_bg_vao.load(bg_verts, bg_indices, bg_attributes);
		m_tile_shader.bind_uniform_block("tiles", m_ubo_binding_index);
		m_tile_map.load(tileset_indices, GL_STATIC_READ);
		m_tile_map.bind_to_uniform_block(m_ubo_binding_index);
		m_tile_map.unbind();
	}

	void RenderEngine::render(const glm::uvec2 world_position)
	{
		m_tile_shader.use();
		m_tile_shader.setUniform_vec2_u("screenSize", glm::uvec2(m_width, m_height));
		m_tile_shader.setUniform_vec2_u("worldCoords", world_position);
		m_tile_shader.setUniform_vec4_u("maskCoords", glm::uvec4(0, 0, 128, 128));
		m_tileset.bind_texture();
		m_frame_buffer.bind();
		m_bg_vao.draw();
		m_frame_buffer.unbind();

		glClear(GL_COLOR_BUFFER_BIT); // Redundant for this application? Move to buffer class/namespace

		m_screen_shader.use();
		m_screen_shader.setUniform_vec2_f("offset", glm::vec2(0.0f, 0.0f));
		m_frame_buffer.bind_colour_buffer();
		m_screen_vao.draw();

		m_screen_position_old = world_position;
	}
}