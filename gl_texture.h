#pragma once

#include "opengl.h"

class Texture
{
private:
	unsigned int texture_ID{ 0 };
public:
	enum class Wrap {
		repeat = GL_REPEAT,
		mirror = GL_MIRRORED_REPEAT,
		extend = GL_CLAMP_TO_EDGE,
		clamp = GL_CLAMP_TO_BORDER
	};

	enum class Filter {
		nearest = GL_NEAREST,
		linear = GL_LINEAR
	};

	Texture();
	~Texture();

	void load_image(const char* path, const Wrap wrap_mode, const Filter filter_mode) const;
	void bind_texture() const;
	void attach_to_frame_buffer() const;
};

