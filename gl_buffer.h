#pragma once

#include "opengl.h"

namespace GLRender
{
	class Buffer
	{
	private:
		GLuint m_buffer_ID;
		GLenum m_target;
		void m_load_buffer(const GLsizeiptr size, const void* data, const GLenum usage) const;
	public:
		Buffer(const GLenum buffer_type);
		Buffer(const Buffer&) = delete;
		Buffer(Buffer&&) = default;
		Buffer& operator=(const Buffer&) = delete;
		Buffer& operator=(Buffer&&) = default;
		~Buffer();

		void bind_to_uniform_block(const GLuint ubo_index) const; // Method only applies to uniform buffers
		void bind_to_texture(GLenum format) const; // Method only applies to texture buffers
		void bind() const;
		void unbind() const;
		//void write(const GLsizeiptr size, const void* data) const;

		template<typename T, size_t S>
		void load(const std::array<T, S> buffer_data, const GLenum usage) const;
	};
	
	template<typename T, size_t S>
	inline void Buffer::load(const std::array<T, S> buffer_data, const GLenum usage) const
	{
		m_load_buffer(S * sizeof(T), buffer_data.data(), usage);
	}

}