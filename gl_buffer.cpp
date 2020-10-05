#include "gl_buffer.h"

Buffer::Buffer()
{
	glGenBuffers(1, &buffer_ID);
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &buffer_ID);
	std::cout << "Buffer Destructor, ID: " << buffer_ID << std::endl;
}

void Buffer::init(GLenum buffer_type, GLsizeiptr size, const void* data, GLenum usage)
{
	glBindBuffer(buffer_type, buffer_ID);
	glBufferData(buffer_type, size, data, usage); // Creates and initialises store. Should be in constructor, use glBufferSubData for updates

	target = buffer_type;
}

void Buffer::bind_uniform_block(GLuint index) const
{
	glBindBufferBase(GL_UNIFORM_BUFFER, index, buffer_ID); // glBindBufferRange for part binding
}

void Buffer::bind() const
{
	glBindBuffer(target, buffer_ID);
}

void Buffer::unbind() const
{
	glBindBuffer(target, 0);
}

// Originally calculated screen mask on CPU and updated vertex buffer. Calculations now performed in shader.
void Buffer::write(GLsizeiptr size, const void* data) const
{
	bind();
	void* mem_ptr = glMapBuffer(target, GL_WRITE_ONLY);
	memcpy(mem_ptr, data, size); // No check on data size, use with caution.
	glUnmapBuffer(target);
	unbind();
}