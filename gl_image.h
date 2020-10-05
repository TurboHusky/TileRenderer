#pragma once
#include "opengl.h"

struct ImageData
{
	const int width;
	const int height;
	const GLint format;
	const unsigned char* data;
};

class Image
{
private:
	int image_width{ 0 };
	int image_height{ 0 };
	GLint GL_format{ GL_RGBA };
	unsigned char* data;
public:
	Image(const char* path);
	Image(const Image&) = delete;
	Image(Image&&) = delete;
	Image& operator=(const Image&) = delete;
	Image& operator=(Image&&) = delete;
	~Image();

	ImageData get_image_data() const;
};