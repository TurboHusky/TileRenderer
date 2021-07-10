#pragma once

#include "opengl.h"
#include "gl_buffer.h"

namespace GLRender
{
	struct VertexAttribute {
		GLint size;
		GLenum type;
		GLboolean normalized;
		GLsizei stride;
		const void* address_offset;
	};

	class VertexArray
	{
	private:
		GLuint m_vertex_array_ID;
		GLuint m_vertex_count;
		Buffer m_vertex_buffer;
		
		void m_build_vertex_array(const std::vector<VertexAttribute> attributes);
	public:
		VertexArray();
		VertexArray(const VertexArray&) = delete;
		VertexArray(VertexArray&&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;
		VertexArray& operator=(VertexArray&&) = delete;
		~VertexArray();

		void bind() const;
		void unbind() const;

		template <typename T, size_t S>
		void load(const std::array<T, S>& vert, const std::vector<VertexAttribute> attributes);
		void draw() const;
	};

	template<typename T, size_t S>
	inline void VertexArray::load(const std::array<T, S>& vert, const std::vector<VertexAttribute> attributes)
	{
		m_vertex_count = sizeof(T) * S;
		m_vertex_buffer.load(vert, GL_STATIC_READ); // !! Magic number
		m_build_vertex_array(attributes);
	}

	class VertexArrayIndexed : public VertexArray {
	private:
		GLuint m_vertex_count;
		Buffer m_element_buffer;

		void m_attach_element_buffer();
	public:
		VertexArrayIndexed();
		VertexArrayIndexed(const VertexArrayIndexed&) = delete;
		VertexArrayIndexed(VertexArrayIndexed&&) = delete;
		VertexArrayIndexed& operator=(const VertexArrayIndexed&) = delete;
		VertexArrayIndexed& operator=(VertexArrayIndexed&&) = delete;
		~VertexArrayIndexed() = default;

		template <typename T_v, size_t S_v, typename T_e, size_t S_e>
		void load(const std::array<T_v, S_v>& vert, const std::array<T_e, S_e>& elem, const std::vector<VertexAttribute> attributes);
		void draw() const;
	};

	template<typename T_v, size_t S_v, typename T_e, size_t S_e>
	inline void VertexArrayIndexed::load(const std::array<T_v, S_v>& vert, const std::array<T_e, S_e>& elem, const std::vector<VertexAttribute> attributes)
	{
		m_vertex_count = sizeof(T_e) * S_e;
		VertexArray::load(vert, attributes);
		m_element_buffer.load(elem, GL_STATIC_READ); // !! Magic number
		m_attach_element_buffer();
	}
}