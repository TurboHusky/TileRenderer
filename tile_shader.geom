#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 6) out;

in uvec2 displacement [];

layout (std140) uniform tileData
{
	uvec2 screenSize;
	uvec2 renderSize;
	uvec2 tileSize;
	uvec2 tileCount;
	uvec2 mapSize;
};

void main() 
{
	vec2 scale = 2.0 * vec2(renderSize) / screenSize; // Map to clip space (-1 to 1)

	for(int i=0; i<3; i++)
	{
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
	EndPrimitive();

	for(int i=0; i<3; i++)
	{
		gl_Position = gl_in[i].gl_Position - vec4(scale * displacement[i], 0.0, 0.0);
		EmitVertex();
	}
	EndPrimitive();
}