#include "gl_vertexarray.h"

namespace GLRender
{
	VertexArray::VertexArray() :
		m_vertex_count{ 0 },
		m_vertex_buffer{ GL_ARRAY_BUFFER }
//		m_DELETE_BUFFER{ GL_ELEMENT_ARRAY_BUFFER }
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

	void VertexArray::m_build_vertex_array(const std::vector<VertexAttribute> attribs)
	{
		glBindVertexArray(m_vertex_array_ID);
		m_vertex_buffer.bind();
		for (auto i = 0; i < attribs.size(); i++)
		{
			glVertexAttribPointer(i, attribs[i].size, attribs[i].type, attribs[i].normalized, attribs[i].stride, attribs[i].address_offset);
			glEnableVertexAttribArray(i);
		}

		glBindVertexArray(0);
		m_vertex_buffer.unbind();
	}

	void VertexArray::draw() const
	{
		bind();
		glDrawArrays(GL_LINES, 0, m_vertex_count);
	}



	void VertexArrayIndexed::m_attach_element_buffer()
	{
		bind();
		m_element_buffer.bind();
		glBindVertexArray(0);
		m_element_buffer.unbind();
	}

	VertexArrayIndexed::VertexArrayIndexed() :
		m_element_buffer{ GL_ELEMENT_ARRAY_BUFFER }
	{
	}

	void VertexArrayIndexed::draw() const
	{
		bind();
		glDrawElements(GL_TRIANGLES, m_vertex_count, GL_UNSIGNED_INT, 0); // Indexed rendering
	}
}