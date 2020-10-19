#include "render_engine.h"
#include <array>

namespace GLRender
{
	RenderEngine::RenderEngine(const unsigned int screen_width, const unsigned int screen_height) :
		m_screen_size{ screen_width, screen_height },
		m_render_size{ 128, 128 },
		m_screen_position_old{ glm::uvec2(0,0) }, //render_width, render_height) },
		m_uniform_binding_point{ 0 },
		m_tex_tileset{ "resources/38056.png", { Texture::ColourMode::rgba, Texture::Wrap::clamp, Texture::Wrap::clamp, Texture::Filter::nearest, Texture::Filter::nearest } },
		m_buff_uniform_data{ GL_UNIFORM_BUFFER },
		m_frame_buffer{ m_render_size.x, m_render_size.y, Texture::ColourMode::rgba },
		m_tile_shader{ "tile_shader.vert", "tile_shader.geom", "tile_shader.frag" },
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
			VertexAttribute { 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) 0 },
			VertexAttribute { 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) (2 * sizeof(float)) }
		};
		m_verts_screen.load(screen_verts, screen_indices, screen_attributes);

		std::array<unsigned int, 96> bg_verts{
			2u, 7u,
			2u, 3u,
			0u, 3u,
			0u, 7u,

			6u, 3u,
			6u, 1u,
			4u, 1u,
			4u, 3u,

			2u, 1u,
			2u, 5u,
			0u, 5u,
			0u, 1u
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
			VertexAttribute{ 2, GL_FLOAT, GL_FALSE, 2 * sizeof(unsigned int), (void*) 0 }
		};
		m_verts_bg.load(bg_verts, bg_indices, bg_attributes);

		// Test code, copies tilemap image
		std::array<unsigned int, 380> tileset_indices;
		for (auto j = 0; j < 304 / 16; j++)
		{
			for (auto i = 0; i < 320 / 16; i++)
			{
				tileset_indices[i + 20 * j] = i + 20u * j;
			}
		}
		m_buff_tex_tile_indices.load(tileset_indices, GL_R32UI);

		std::array<unsigned int, 10> tile_data{ 
			m_screen_size.x, m_screen_size.y,
			m_render_size.x, m_render_size.y,
			16u, 16u,			// Tile size
			20u, 19u,			// Tile count
			20u, 19u			// Map size
		};
		m_buff_uniform_data.load(tile_data, GL_STATIC_READ);

		// Texture binding, needs encapsulating
		glActiveTexture(GL_TEXTURE0);
		m_buff_tex_tile_indices.bind();
		glActiveTexture(GL_TEXTURE1);
		m_tex_tileset.bind();

		// Shader setup
		m_tile_shader.use();
		m_buff_uniform_data.bind_to_uniform_block(m_uniform_binding_point);
		m_tile_shader.bind_uniform_block("tileData", m_uniform_binding_point);
		m_tile_shader.setUniform_i("indexBuffer", 0);
		m_tile_shader.setUniform_i("tileTexture", 1);
	}

	void RenderEngine::render(const glm::uvec2 world_position)
	{
		m_tile_shader.use();
		GLuint newCoords[8]{ 16u, 16u, 80u, 80u, 0u, 0u, 128u, 128u };
		m_tile_shader.setUniform_1uiv("renderArea", 8, &newCoords[0]);
		m_tile_shader.setUniform_uvec2("worldOffset", glm::uvec2(world_position));

		m_tex_tileset.bind();
		m_frame_buffer.bind();
		m_verts_bg.draw();
		m_frame_buffer.unbind();

		//glClear(GL_COLOR_BUFFER_BIT); // Not yet needed.

		m_screen_shader.use();
		glm::vec2 screen_offset{ (float)(world_position.x % m_render_size.x) / m_render_size.x, (float)(world_position.y % m_render_size.y) / m_render_size.y };
		m_screen_shader.setUniform_vec2("screenOffset", screen_offset);
		//m_frame_buffer.bind_colour_buffer();
		m_verts_screen.draw();

		m_screen_position_old = world_position;
	}
}