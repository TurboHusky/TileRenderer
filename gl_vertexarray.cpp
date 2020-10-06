#include "gl_vertexarray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &vertex_array_ID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &vertex_array_ID);
	std::cout << "Vertex Array Destructor, ID: " << vertex_array_ID << std::endl;
}

void VertexArray::bind() const
{
	glBindVertexArray(vertex_array_ID);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::init(const GLsizeiptr v_size, const void* v_data, const GLsizeiptr e_size, const void* e_data, const GLenum usage, const std::vector<VertexAttribute> attribs)
{
	vertex_buffer.load(v_size, usage, v_data);
	element_buffer.load(e_size, usage, e_data);

	glBindVertexArray(vertex_array_ID);
	vertex_buffer.bind();
	element_buffer.bind();
	for (auto i = 0; i < attribs.size(); i++)
	{
		glVertexAttribPointer(i, attribs[i].size, attribs[i].type, attribs[i].normalized, attribs[i].stride, attribs[i].attribute_offset);
		glEnableVertexAttribArray(i);
	}

	glBindVertexArray(0);
	vertex_buffer.unbind();
	element_buffer.unbind();
	vertex_count = e_size;
}

void VertexArray::draw() const
{
	bind();
	glDrawElements(GL_TRIANGLES, vertex_count, GL_UNSIGNED_INT, 0);
}