#include "gl_framebuffer.h"

namespace GLRender
{
	FrameBuffer::FrameBuffer(GLint width, GLint height, Texture::ColourMode format) :
		m_colour_buffer
		{ 
			width,
			height,
			{ 
				Texture::ColourMode::rgba,
				Texture::Wrap::clamp,
				Texture::Wrap::clamp,
				Texture::Filter::nearest,
				Texture::Filter::nearest
			}
		}
	{
		glGenFramebuffers(1, &m_frame_buffer_ID);

		glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer_ID);
		m_colour_buffer.bind();
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		m_colour_buffer.attach_to_frame_buffer();
		// No depth or stencil buffers used

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER::Incomplete buffer" << std::endl;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffers(1, &m_frame_buffer_ID);
		std::cout << "Frame Buffer Destructor, ID: " << m_frame_buffer_ID << std::endl;
	}

	void FrameBuffer::bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer_ID);
	}

	void FrameBuffer::bind_colour_buffer() const
	{
		m_colour_buffer.bind();
	}

	void FrameBuffer::unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}