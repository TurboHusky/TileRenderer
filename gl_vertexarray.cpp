#include "gl_vertexarray.h"

namespace GLRender
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &m_vertex_array_ID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_vertex_array_ID);
		std::cout << "Vertex Array Destructor, ID: " << m_vertex_array_ID << std::endl;
	}

	void VertexArray::bind() const
	{
		glBindVertexArray(m_vertex_array_ID);
	}

	void VertexArray::unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::init(const GLsizeiptr v_size, const void* v_data, const GLsizeiptr e_size, const void* e_data, const GLenum usage, const std::vector<VertexAttribute> attribs)
	{
		m_vertex_buffer.load(v_size, usage, v_data);
		m_element_buffer.load(e_size, usage, e_data);

		glBindVertexArray(m_vertex_array_ID);
		m_vertex_buffer.bind();
		m_element_buffer.bind();
		for (auto i = 0; i < attribs.size(); i++)
		{
			glVertexAttribPointer(i, attribs[i].size, attribs[i].type, attribs[i].normalized, attribs[i].stride, attribs[i].address_offset);
			glEnableVertexAttribArray(i);
		}

		glBindVertexArray(0);
		m_vertex_buffer.unbind();
		m_element_buffer.unbind();
		m_vertex_count = e_size;
	}

	void VertexArray::draw() const
	{
		bind();
		glDrawElements(GL_TRIANGLES, m_vertex_count, GL_UNSIGNED_INT, 0);
	}
}