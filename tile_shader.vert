#version 330 core
layout (location = 0) in uvec2 coordIndex;

// !! Mask values need to be mapped to screen area prior to being passed to shader.
uniform uint renderArea[8]; // bottom left / top right xy coords for mask area and screen

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
	vec2 vertPos = ((2.0 * vec2(renderArea[coordIndex.x], renderArea[coordIndex.y])) / screenSize) - 1.0; // Clip space mapping (-1 to 1)
	gl_Position = vec4(vertPos, 0.0, 1.0);
}