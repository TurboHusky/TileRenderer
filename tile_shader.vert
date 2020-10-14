#version 330 core
layout (location = 0) in uvec3 xMaskCoeffs;
layout (location = 1) in uvec3 yMaskCoeffs;

uniform uvec4 maskCoords; // Input is in pixels, xy = bottom left, zw = top right

layout (std140) uniform tileData
{
	uvec2 screenSize;
	uvec2 tileSize;
	uvec2 tileCount;
	uvec2 mapSize;
};

// Must pass integers to frag shader as flat, cannot interpolate

void main()
{	
	vec2 glPos;
	glPos.x = xMaskCoeffs.x * maskCoords.x + xMaskCoeffs.y * maskCoords.z + xMaskCoeffs.z;
	glPos.y = yMaskCoeffs.x * maskCoords.y + yMaskCoeffs.y * maskCoords.w + yMaskCoeffs.z;

	glPos = (glPos * 2.0) / vec2(screenSize) - 1.0; // Clip space (-1 to 1)
	gl_Position = vec4(glPos, 0.0, 1.0);
}