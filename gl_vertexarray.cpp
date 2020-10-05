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

void VertexArray::init(GLsizeiptr vertex_data_size, const void* vertex_data, GLsizeiptr element_data_size, const void* element_data, GLenum usage)
{
	glBindVertexArray(vertex_array_ID);

	vertex_buffer.init(GL_ARRAY_BUFFER, vertex_data_size, vertex_data, usage);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0); // Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float))); // Texture Coords
	glEnableVertexAttribArray(1);

	element_buffer.init(GL_ELEMENT_ARRAY_BUFFER, element_data_size, element_data, usage);

	glBindVertexArray(0);
	vertex_buffer.unbind();
	element_buffer.unbind();

	vertex_count = element_data_size;
}

void VertexArray::init_custom(GLsizeiptr vertex_data_size, const void* vertex_data, GLsizeiptr element_data_size, const void* element_data, GLenum usage)
{
	glBindVertexArray(vertex_array_ID);

	vertex_buffer.init(GL_ARRAY_BUFFER, vertex_data_size, vertex_data, usage);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); // x coefficients
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // y coefficients
	glEnableVertexAttribArray(1);

	element_buffer.init(GL_ELEMENT_ARRAY_BUFFER, element_data_size, element_data, usage);

	glBindVertexArray(0);
	vertex_buffer.unbind();
	element_buffer.unbind();

	vertex_count = element_data_size;
}

void VertexArray::draw() const
{
	bind();
	glDrawElements(GL_TRIANGLES, vertex_count, GL_UNSIGNED_INT, 0);
}