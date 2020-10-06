#pragma once

#include "opengl.h"
#include "gl_texture.h"


class Buffer
{
private:
	GLuint buffer_ID{ 0 };
	GLenum target{ 0 };
public:
	Buffer(const GLenum buffer_type);
	/*template<typename T>
	Buffer(const GLenum buffer_type, const GLarrayWrapper<T>& buffer_data, const GLenum usage);*/
	Buffer(const Buffer&) = delete;
	Buffer(Buffer&&);
	Buffer& operator=(const Buffer&) = delete;
	Buffer& operator=(Buffer&&);
	~Buffer();

	void bind_to_uniform_block(GLuint ubo_index) const; // Method only applies to uniform buffer?
	void bind() const;
	void unbind() const;
	void load(const GLsizeiptr size, const GLenum usage, const void* data) const; // NEEDS TO BE SIMPLIFIED
	//void write(const GLsizeiptr size, const void* data) const;
};

// Not currently used. Implement if needed
/*template<typename T>
inline Buffer::Buffer(const GLenum buffer_type, const GLarrayWrapper<T>& buffer_data, const GLenum usage) : target{ buffer_type }
{
	glGenBuffers(1, &buffer_ID);
	load(buffer_data.size, usage, buffer_data.data);
}*/
