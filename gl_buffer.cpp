#include "gl_buffer.h"
#include <utility>

namespace GLRender
{
	void Buffer::load_buffer(const GLsizeiptr size, const void* data, const GLenum usage) const
	{
		glBindBuffer(m_target, m_buffer_ID);
		// TODO: Add checks, resizing/reallocating function
		glBufferData(m_target, size, data, usage);
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