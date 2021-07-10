#include "gl_texture.h"

namespace GLRender
{
	Texture::Texture(const char* image_path, const Texture_Settings settings)
	{
		glGenTextures(1, &m_texture_ID);
		load_image(image_path, settings);
	}

	Texture::Texture(const GLint tex_width, const GLint tex_height, const Texture_Settings settings) :
		m_width{ tex_width },
		m_height{ tex_height }
	{
		glGenTextures(1, &m_texture_ID);
		glBindTexture(GL_TEXTURE_2D, m_texture_ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, settings.wrap_horizontal);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, settings.wrap_vertical);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, settings.filter_min);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, settings.filter_mag);

		glTexImage2D(GL_TEXTURE_2D, 0, settings.mode, m_width, m_height, 0, GL_RED, GL_UNSIGNED_BYTE, NULL); // Allocate/reallocate memory
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_texture_ID);
		std::cout << "Texture Destructor, " << m_width << "x" << m_height << ", ID: " << m_texture_ID << std::endl;
	}

	void Texture::load_image(const char* path, const Texture_Settings settings) const
	{
		try 
		{ 
			Image image(path);

			glBindTexture(GL_TEXTURE_2D, m_texture_ID);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, settings.wrap_horizontal);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, settings.wrap_vertical);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, settings.filter_min);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, settings.filter_mag);

			if (image.width() == m_width && image.height() == m_height)
			{
				glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_width, m_height, image.colour_format(), GL_UNSIGNED_BYTE, image.data());
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, settings.mode, image.width(), image.height(), 0, image.colour_format(), GL_UNSIGNED_BYTE, image.data());
				m_width = image.width();
				m_height = image.height();
			}
			glBindTexture(GL_TEXTURE_2D, 0);
		}
		catch(std::exception e)
		{
			std::cout << e.what();
			std::cout << "gl_texture::Image failed to load" << std::endl;
		}
	}

	void Texture::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_texture_ID);
	}

	void Texture::attach_to_frame_buffer() const
	{
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texture_ID, 0);
	}

	void BufferTexture::m_bind_buffer(GLenum format)
	{
		glBindTexture(GL_TEXTURE_BUFFER, m_buffer_texture_ID);
		m_data.bind_to_texture(format);
		glBindTexture(GL_TEXTURE_BUFFER, 0);
	}

	BufferTexture::BufferTexture() :
		m_data{ GL_TEXTURE_BUFFER }
	{
		glGenTextures(1, &m_buffer_texture_ID);
	}

	BufferTexture::~BufferTexture()
	{
		glDeleteTextures(1, &m_buffer_texture_ID);
		std::cout << "Buffer Texture Destructor, ID: " << m_buffer_texture_ID << std::endl;
	}

	void BufferTexture::bind()
	{
		glBindTexture(GL_TEXTURE_BUFFER, m_buffer_texture_ID);
	}
}