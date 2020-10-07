#pragma once
#include "opengl.h"

namespace GLRender
{
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
		int m_width;
		int m_height;
		GLint m_colour_format;
		unsigned char* m_data;
	public:
		Image(const char* path);
		Image(const Image&) = delete;
		Image(Image&&) = delete;
		Image& operator=(const Image&) = delete;
		Image& operator=(Image&&) = delete;
		~Image();

		ImageData get_image_data() const;
	};
}