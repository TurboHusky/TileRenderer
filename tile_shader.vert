#version 330 core
layout (location = 0) in uvec3 xMaskCoeffs;
layout (location = 1) in uvec3 yMaskCoeffs;

uniform uvec4 maskCoords; // Input is in pixels, xy = bottom left, zw = top right

layout (std140) uniform tileData
{
	uvec2 screenSize;
	uvec2 renderSize;
	uvec2 tileSize;
	uvec2 tileCount;
	uvec2 mapSize;
};

// Must pass integers to frag shader as flat, cannot interpolate
out vec2 texCoords;

void main()
{	
	uvec4 test = maskCoords / uvec4(renderSize, renderSize);
	test = maskCoords - test * uvec4(renderSize, renderSize);
	
	texCoords.x = xMaskCoeffs.x * test.x + xMaskCoeffs.y * test.z + xMaskCoeffs.z;
	texCoords.y = yMaskCoeffs.x * test.y + yMaskCoeffs.y * test.w + yMaskCoeffs.z;

	vec2 vertPos = ((2.0 * texCoords) / screenSize) - 1.0; // Use screen coords to map mask to clip space (-1 to 1)

	gl_Position = vec4(vertPos, 0.0, 1.0);
}