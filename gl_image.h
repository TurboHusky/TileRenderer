#pragma once
#include "opengl.h"

namespace GLRender
{
	class Image
	{
	private:
		int m_width;
		int m_height;
		GLint m_colour_format;
		unsigned char* m_data{ nullptr };
	public:
		Image(const char* path);
		Image(const Image&) = delete;
		Image(Image&&) = delete;
		Image& operator=(const Image&) = delete;
		Image& operator=(Image&&) = delete;
		~Image();

		int width() const;
		int height() const;
		GLint colour_format() const;
		unsigned char* data() const;
	};
}