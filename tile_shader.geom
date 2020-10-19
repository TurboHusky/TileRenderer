#version 330 core
layout (lines) in; // Needs to match draw method in vertex array
layout (triangle_strip, max_vertices = 36) out;

layout (std140) uniform tileData
{
	uvec2 screenSize;
	uvec2 renderSize;
	uvec2 tileSize;
	uvec2 tileCount;
	uvec2 mapSize;
};

uniform vec2 start;
uniform vec2 end;

void drawTriangle(vec2 vertex1, vec2 vertex2, vec2 vertex3)
{
	gl_Position = vec4(vertex1, 0.0, 1.0);
	EmitVertex();
	gl_Position = vec4(vertex2, 0.0, 1.0);
	EmitVertex();
	gl_Position = vec4(vertex3, 0.0, 1.0);
	EmitVertex();
	EndPrimitive();
}

void drawSquare(vec2 bottom_left, vec2 top_right)
{
	vec2 bottom_right = vec2(top_right.x, bottom_left.y);
	vec2 top_left = vec2(bottom_left.x, top_right.y);

	drawTriangle(top_right, bottom_right, top_left);
	drawTriangle(bottom_right, bottom_left, top_left);
}

void main() 
{
	vec2 bottom_left_world = min(start, end);
	vec2 bottom_left_screen = mod(bottom_left_world, renderSize);
	vec2 offset = max(start, end) - bottom_left_world;

	vec2 screen_edge_normalised = 2.0f * renderSize / screenSize;

	vec4 normalised_screen = 2.0f * vec4(bottom_left_screen, bottom_left_screen + max(start, end) - bottom_left_world) / vec4(screenSize, screenSize) - 1.0;
	vec2 bottom_left_normalised = 2.0f * bottom_left_screen / screenSize - 1.0;
	vec2 top_right_normalised = 2.0f * (bottom_left_screen + max(start, end) - bottom_left_world) / screenSize - 1.0;

	drawSquare(vec2(bottom_left_normalised.x, top_right_normalised.y), vec2(top_right_normalised.x, 1.0f));
	drawSquare(vec2(-1.0f, bottom_left_normalised.y), vec2(1.0f, top_right_normalised.y));
	drawSquare(vec2(bottom_left_normalised.x, -1.0f), vec2(top_right_normalised.x, bottom_left_normalised.y));

	drawSquare(vec2(bottom_left_normalised.x, top_right_normalised.y) - vec2(screen_edge_normalised.x, 0.0f), vec2(top_right_normalised.x, 1.0f) - vec2(screen_edge_normalised.x, 0.0f));
	drawSquare(vec2(-1.0f, bottom_left_normalised.y) - vec2(0.0f, screen_edge_normalised.y), vec2(1.0f, top_right_normalised.y) - vec2(0.0f, screen_edge_normalised.y));
	drawSquare(vec2(bottom_left_normalised.x, -1.0f) - vec2(screen_edge_normalised.x, 0.0f), vec2(top_right_normalised.x, bottom_left_normalised.y) - vec2(screen_edge_normalised.x, 0.0f));
}