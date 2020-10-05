#pragma once

#include "opengl.h"
#include "gl_image.h"


class Texture
{
private:
	unsigned int texture_ID{ 0 };
	mutable int width{ 0 };
	mutable int height{ 0 };
public:
	enum ColourMode {
		r = GL_R8,
		rg = GL_RG8,
		rgb = GL_RGB8,
		rgba = GL_RGBA8 // sRGB colour formats
	};

	enum Wrap {
		repeat = GL_REPEAT,
		mirror = GL_MIRRORED_REPEAT,
		extend = GL_CLAMP_TO_EDGE,
		clamp = GL_CLAMP_TO_BORDER
	};

	enum Filter {
		nearest = GL_NEAREST,
		linear = GL_LINEAR
	};

	struct Texture_Settings {
		ColourMode mode;
		Wrap wrap_horizontal;
		Wrap wrap_vertical;
		Filter filter_mag;
		Filter filter_min;
	};

	Texture(const char* image_path, const Texture_Settings settings);
	Texture(const GLint width, const GLint height, const Texture_Settings settings);
	Texture(const Texture&) = delete;
	Texture(Texture&&) = delete;
	Texture& operator=(const Texture&) = delete;
	Texture& operator=(Texture&&) = delete;
	~Texture();
		
	void load_image(const char* path, const Texture_Settings settings) const;
	void bind_texture() const;
	void attach_to_frame_buffer() const;
};