#include "gl_buffer.h"
#include <utility>


Buffer::Buffer(const GLenum buffer_type) :
	target{ buffer_type }
{
	glGenBuffers(1, &buffer_ID);
}

Buffer::Buffer(Buffer&& other)
{
	std::swap(buffer_ID, other.buffer_ID);
	std::swap(target, other.target);
}

Buffer& Buffer::operator=(Buffer&& other)
{
	std::swap(buffer_ID, other.buffer_ID);
	std::swap(target, other.target);
	
	return other;
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &buffer_ID);
	std::cout << "Buffer Destructor, ID: " << buffer_ID << std::endl;
}

void Buffer::load(const GLsizeiptr size, const GLenum usage, const void* data) const
{
	glBindBuffer(target, buffer_ID);
	glBufferData(target, size, data, usage); // Creates and initialises store. Should be in constructor, use glBufferSubData for updates
}

void Buffer::bind_to_uniform_block(GLuint ubo_index) const
{
	// !! target must be valid, should check.
	glBindBufferBase(GL_UNIFORM_BUFFER, ubo_index, buffer_ID); // glBindBufferRange to bind part of buffer
}

void Buffer::bind() const
{
	glBindBuffer(target, buffer_ID);
}

void Buffer::unbind() const
{
	glBindBuffer(target, 0);
}

// Unused Function for explicit CPU to GPU copies, no check on data size, unsafe.
/*void Buffer::write(GLsizeiptr size, const void* data) const
{
	bind();
	void* mem_ptr = glMapBuffer(target, GL_WRITE_ONLY);
	memcpy(mem_ptr, data, size);
	glUnmapBuffer(target);
	unbind();
}*/