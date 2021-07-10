#include "gl_image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace GLRender
{
	Image::Image(const char* path)
	{
		int nrChannels;

		stbi_set_flip_vertically_on_load(true);
		m_data = stbi_load(path, &m_width, &m_height, &nrChannels, 0);

		if (m_data == nullptr)
		{
			throw std::runtime_error("gl_image::Can't open file\n");
			return;
		}

		switch (nrChannels)
		{
		case 1:
			m_colour_format = GL_RED;
			break;
		case 2:
			m_colour_format = GL_RG;
			break;
		case 3:
			m_colour_format = GL_RGB;
			break;
		default:
			m_colour_format = GL_RGBA;
		}
	}

	Image::~Image()
	{
		stbi_image_free(m_data);
		std::cout << "Image Destructor" << std::endl;
	}

	ImageData Image::get_image_data() const
	{
		return { m_width, m_height, m_colour_format, m_data };
	}
}