#include "gl_buffer.h"
#include <utility>

namespace GLRender
{
	Buffer::Buffer(const GLenum buffer_type) :
		m_target{ buffer_type }
	{
		glGenBuffers(1, &m_buffer_ID);
	}

	Buffer::Buffer(Buffer&& other)
	{
		std::swap(m_buffer_ID, other.m_buffer_ID);
		std::swap(m_target, other.m_target);
	}

	Buffer& Buffer::operator=(Buffer&& other)
	{
		std::swap(m_buffer_ID, other.m_buffer_ID);
		std::swap(m_target, other.m_target);

		return other;
	}

	Buffer::~Buffer()
	{
		glDeleteBuffers(1, &m_buffer_ID);
		std::cout << "Buffer Destructor, ID: " << m_buffer_ID << std::endl;
	}

	void Buffer::load(const GLsizeiptr size, const GLenum usage, const void* data) const
	{
		glBindBuffer(m_target, m_buffer_ID);
		glBufferData(m_target, size, data, usage); // Creates and initialises store. Should be in constructor, use glBufferSubData for updates
	}

	void Buffer::bind_to_uniform_block(GLuint ubo_index) const
	{
		// !! target must be valid, should check.
		glBindBufferBase(GL_UNIFORM_BUFFER, ubo_index, m_buffer_ID); // glBindBufferRange to bind part of buffer
	}

	void Buffer::bind() const
	{
		glBindBuffer(m_target, m_buffer_ID);
	}

	void Buffer::unbind() const
	{
		glBindBuffer(m_target, 0);
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
}