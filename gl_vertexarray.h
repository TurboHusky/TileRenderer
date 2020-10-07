#pragma once

#include "opengl.h"
#include "gl_buffer.h"

#include <vector>

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
		GLuint m_vertex_array_ID{ 0 };
		GLuint m_vertex_count{ 0 };
		Buffer m_vertex_buffer{ GL_ARRAY_BUFFER };
		Buffer m_element_buffer{ GL_ELEMENT_ARRAY_BUFFER };
	public:
		VertexArray();
		VertexArray(const VertexArray&) = delete;
		VertexArray(VertexArray&&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;
		VertexArray& operator=(VertexArray&&) = delete;
		~VertexArray();

		void bind() const;
		void unbind() const;
		void init(const GLsizeiptr v_size, const void* v_data, const GLsizeiptr e_size, const void* e_data, const GLenum usage, const std::vector<VertexAttribute> attribs);
		template <typename V, typename E>
		void init_new(const GLarrayWrapper<V>& vert, const GLarrayWrapper<E>& elem, const std::vector<VertexAttribute> attribs);
		void draw() const;
	};

	template<typename V, typename E>
	inline void VertexArray::init_new(const GLarrayWrapper<V>& vert, const GLarrayWrapper<E>& elem, const std::vector<VertexAttribute> attribs)
	{
		init(vert.size, vert.data, elem.size, elem.data, GL_STATIC_READ, attribs);
	}
}