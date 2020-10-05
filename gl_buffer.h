#pragma once

#include "opengl.h"
#include "gl_texture.h"

/* Have different buffers
	- GL_UNIFORM_BUFFER in render_engine 
	- GL_ARRAY_BUFFER in Vertex Array
	- GL_ELEMENT_ARRAY_BUFFER in Vertex Array */
class Buffer // MAKE THIS BASE CLASS, EXTEND FOR ALTERNATE TARGETS
{
private:
	GLuint buffer_ID{ 0 };
	GLenum target{ 0 };
public:
	Buffer();
	Buffer(const Buffer&) = delete;
	Buffer(Buffer&&) = delete;
	Buffer& operator=(const Buffer&) = delete;
	Buffer& operator=(Buffer&&) = delete;
	~Buffer();

	void bind_uniform_block(GLuint index) const; // Method is only for uniform buffer
	void bind() const;
	void unbind() const;
	void init(GLenum buffer_type, GLsizeiptr size, const void* data, GLenum usage); // NEEDS TO BE SIMPLIFIED
	void write(GLsizeiptr size, const void* data) const;
};