#include "gl_image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Image::Image(const char* path)
{
	int nrChannels;
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(path, &image_width, &image_height, &nrChannels, 0);

	switch (nrChannels)
	{
	case 1:
		GL_format = GL_RED;
		break;
	case 2:
		GL_format = GL_RG;
		break;
	case 3:
		GL_format = GL_RGB;
		break;
	default:
		GL_format = GL_RGBA;
	}
}

Image::~Image()
{
	stbi_image_free(data);
	std::cout << "Image Destructor" << std::endl;
}

ImageData Image::get_image_data() const
{
	return { image_width, image_height, GL_format, data };
}
