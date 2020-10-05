#include "gl_texture.h"

Texture::Texture(const char* image_path, const Texture_Settings settings)
{
	glGenTextures(1, &texture_ID);
	load_image(image_path, settings);
}

Texture::Texture(const GLint tex_width, const GLint tex_height, const Texture_Settings settings) :
	width{ tex_width }, 
	height{ tex_height }
{
	glGenTextures(1, &texture_ID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, settings.wrap_horizontal);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, settings.wrap_vertical);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, settings.filter_min);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, settings.filter_mag);

	glTexImage2D(GL_TEXTURE_2D, 0, settings.mode, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, NULL); // Allocate/reallocate memory
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture_ID);
	std::cout << "Texture Destructor, " << width << "x" << height << ", ID: " << texture_ID << std::endl;
}

void Texture::load_image(const char* path, const Texture_Settings settings) const
{
	Image image(path);
	ImageData image_data = image.get_image_data();

	if(image_data.data)
	{
		glBindTexture(GL_TEXTURE_2D, texture_ID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, settings.wrap_horizontal);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, settings.wrap_vertical);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, settings.filter_min);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, settings.filter_mag);

		if (image_data.width == width && image_data.height == height)
		{				
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, image_data.format, GL_UNSIGNED_BYTE, image_data.data);				
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, settings.mode, image_data.width, image_data.height, 0, image_data.format, GL_UNSIGNED_BYTE, image_data.data);
			width = image_data.width;
			height = image_data.height;
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else
	{
		std::cout << "Failed to load image" << std::endl;
	}
}

void Texture::bind_texture() const
{
	glBindTexture(GL_TEXTURE_2D, texture_ID);
}

void Texture::attach_to_frame_buffer() const
{
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_ID, 0);
}