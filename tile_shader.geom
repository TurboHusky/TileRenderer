#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

void main() // Use screen coords to map mask to clip space (-1 to 1)
{
	for(int i=0; i<3; i++)
	{
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
	EndPrimitive();
}