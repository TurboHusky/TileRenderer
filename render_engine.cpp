#include "render_engine.h"

RenderEngine::RenderEngine(const unsigned int screen_width, const unsigned int screen_height) : 
	width{ screen_width }, 
	height{ screen_height }, 
	screen_position_old{ glm::uvec2(screen_width, screen_height) },
	ubo_binding_index{ 0 },	
	tileset{ "resources/38056.png", { Texture::ColourMode::rgba, Texture::Wrap::clamp, Texture::Wrap::clamp, Texture::Filter::nearest, Texture::Filter::nearest } },
	frame_buffer{ screen_width, screen_height, Texture::ColourMode::rgba },
	tile_shader{ "tile_shader.vert", "tile_shader.frag" },
	screen_shader{ "screen.vert", "screen.frag" }
{
	float fullscreen[] = {
		// position			// UV
		 1.0f,  1.0f,		1.0f, 1.0f,		// top right
		 1.0f, -1.0f,		1.0f, 0.0f,		// bottom right
		-1.0f, -1.0f,		0.0f, 0.0f,		// bottom left
		-1.0f,  1.0f,		0.0f, 1.0f		// top left
	};

	unsigned int screen_indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	GLarrayWrapper<float> fs_vert{ fullscreen };
	GLarrayWrapper<unsigned int> fs_elem{ screen_indices };
	std::vector<VertexAttribute> VAO_S
	{
		VertexAttribute { 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0 },
		VertexAttribute { 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)) }
	};

	full_screen.init_new(fs_vert, fs_elem, VAO_S);

	unsigned int screenmask_coefficients[] = {
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

	unsigned int mask_indices[] = {
		0, 1, 3,
		1, 2, 3,
		4, 5, 7,
		5, 6, 7,
		8, 9, 11,
		9, 10, 11
	};

	GLarrayWrapper<unsigned int> sm_vert{ screenmask_coefficients };
	GLarrayWrapper<unsigned int> sm_elem{ mask_indices };
	std::vector<VertexAttribute> VAO_M
	{
		VertexAttribute{ 3, GL_UNSIGNED_INT, GL_FALSE, 6 * sizeof(unsigned int), (void*)0 },
		VertexAttribute{ 3, GL_UNSIGNED_INT, GL_FALSE, 6 * sizeof(unsigned int), (void*)(3 * sizeof(unsigned int)) }
	};

	screen_mask.init_new(sm_vert, sm_elem, VAO_M);

	// Test code, copies tilemap image
	glm::uvec2 tile_indices[380];
	for (auto j = 0; j < 304 / 16; j++)
	{
		for (auto i = 0; i < 320 / 16; i++)
		{
			tile_indices[i + 20 * j] = glm::uvec2(i * 16u, j * 16u);
		}
	}

	tile_shader.bind_uniform_block("tiles", ubo_binding_index);
	tile_map.load(sizeof(tile_indices), GL_STATIC_READ, tile_indices);
	tile_map.bind_to_uniform_block(ubo_binding_index);
	tile_map.unbind();
	
	/*GLint temp = tile_shader.get_ubo_size(ubo_binding_index);
	std::cout << "Size of tile index array in bytes : " << sizeof(tile_indices) << std::endl;
	std::cout << "Size of UBO structure in bytes : " << temp << std::endl;*/
}

void RenderEngine::render(const glm::uvec2 world_position)
{
	tile_shader.use();
	tile_shader.setUniform_vec2_u("screenSize", glm::uvec2(width, height));
	tile_shader.setUniform_vec2_u("worldCoords", world_position);
	tile_shader.setUniform_vec4_u("maskCoords", glm::uvec4(0, 0, 128, 128));
	tileset.bind_texture();
	frame_buffer.bind();
	screen_mask.draw();
	frame_buffer.unbind();
	
	glClear(GL_COLOR_BUFFER_BIT); // Redundant for this application? Move to buffer class/namespace

	screen_shader.use();
	screen_shader.setUniform_vec2_f("offset", glm::vec2(0.0f, 0.0f));
	frame_buffer.bind_colour_buffer();
	full_screen.draw();

	screen_position_old = world_position;
}