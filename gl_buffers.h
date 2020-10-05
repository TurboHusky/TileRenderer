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

class FrameBuffer
{
private:
	GLuint frame_buffer_ID{ 0 };
	Texture colour_buffer;
public:
	FrameBuffer(GLint width, GLint height, Texture::ColourMode format);
	FrameBuffer(const FrameBuffer&) = delete;
	FrameBuffer(FrameBuffer&&) = delete;
	FrameBuffer& operator=(const FrameBuffer&) = delete;
	FrameBuffer& operator=(FrameBuffer&&) = delete;
	~FrameBuffer();

	void bind() const;
	void bind_colour_buffer() const;
	void unbind() const;
};

class VertexArray
{
private:
	GLuint vertex_array_ID{ 0 };
	GLuint vertex_count{ 0 };
	Buffer vertex_buffer;
	Buffer element_buffer;
public:
	VertexArray();
	VertexArray(const VertexArray&) = delete;
	VertexArray(VertexArray&&) = delete;
	VertexArray& operator=(const VertexArray&) = delete;
	VertexArray& operator=(VertexArray&&) = delete;
	~VertexArray();

	void bind() const;
	void unbind() const;
	// Need better way to intialise. These load data into buffers and set attributes, should pass attributes as struct for better flexibility.
	void init(GLsizeiptr vertex_data_size, const void* vertex_data, GLsizeiptr element_data_size, const void* element_data, GLenum usage);
	void init_custom(GLsizeiptr vertex_data_size, const void* vertex_data, GLsizeiptr element_data_size, const void* element_data, GLenum usage);
	void draw() const;
};