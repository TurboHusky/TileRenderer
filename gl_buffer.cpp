#include "gl_buffer.h"
#include <utility>

namespace GLRender
{
	void Buffer::m_load_buffer(const GLsizeiptr size, const void* data, const GLenum usage) const
	{
		// TODO: Add checks, resizing/reallocating function
		glBindBuffer(m_target, m_buffer_ID);
		glBufferData(m_target, size, data, usage); // glBufferSubData replaces part of existing buffer
		glBindBuffer(m_target, 0);
	}

	Buffer::Buffer(const GLenum buffer_type) :
		m_target{ buffer_type }
	{
		glGenBuffers(1, &m_buffer_ID);
	}

	Buffer::~Buffer()
	{
		glDeleteBuffers(1, &m_buffer_ID);
		std::cout << "Buffer Destructor, ID: " << m_buffer_ID << std::endl;
	}

	void Buffer::bind_to_uniform_block(GLuint ubo_index) const
	{
		// TODO: Add check for valid target instead of using fixed GL_UNIFORM_BUFFER
		glBindBuffer(m_target, m_buffer_ID);
		glBindBufferBase(GL_UNIFORM_BUFFER, ubo_index, m_buffer_ID); // glBindBufferRange to bind part of buffer
		glBindBuffer(m_target, 0);
	}

	void Buffer::bind_to_texture(GLenum format) const
	{
		glBindBuffer(m_target, m_buffer_ID);
		glTexBuffer(GL_TEXTURE_BUFFER, format, m_buffer_ID);
		glBindBuffer(m_target, 0);
	}

	void Buffer::bind() const
	{
		glBindBuffer(m_target, m_buffer_ID);
	}

	void Buffer::unbind() const
	{
		glBindBuffer(m_target, 0);
	}
}