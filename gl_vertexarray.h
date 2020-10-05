#pragma once

#include "opengl.h"
#include "gl_buffer.h"

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
