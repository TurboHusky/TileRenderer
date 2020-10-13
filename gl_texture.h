#pragma once

#include "opengl.h"
#include "gl_image.h"
#include "gl_buffer.h"

namespace GLRender
{
	class Texture
	{
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
	private:
		unsigned int m_texture_ID;
		mutable int m_width;
		mutable int m_height;
	public:
		Texture(const char* image_path, const Texture_Settings settings);
		Texture(const GLint width, const GLint height, const Texture_Settings settings);
		Texture(const Texture&) = delete;
		Texture(Texture&&) = delete;
		Texture& operator=(const Texture&) = delete;
		Texture& operator=(Texture&&) = delete;
		~Texture();

		void load_image(const char* path, const Texture_Settings settings) const;
		void bind() const;
		void attach_to_frame_buffer() const;
	};

	class BufferTexture
	{
	private:
		GLuint m_buffer_texture_ID;
		Buffer m_data;

		void m_bind_buffer(GLenum format);
	public:
		BufferTexture();
		~BufferTexture();
		
		void bind();

		template<typename T, size_t S>
		void load(std::array<T, S> data, GLenum format);
	};

	template<typename T, size_t S>
	void BufferTexture::load(std::array<T, S> data, GLenum format)
	{
		m_data.load(data, GL_STATIC_READ);
		m_bind_buffer(format);
	}
}