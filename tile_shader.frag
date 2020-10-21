#version 330 core
out vec4 FragColor;

uniform usamplerBuffer indexBuffer;
uniform sampler2D tileTexture;
uniform uvec2 worldOffset;

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
	uvec2 localCoords = uvec2(gl_FragCoord); // gl_FragCoord is in screen space
	uvec2 screenCount = (renderSize - 1u - localCoords + worldOffset) / renderSize;
	uvec2 pixelCoords = (screenCount * renderSize) + localCoords;

	uvec2 tileIndices = pixelCoords / tileSize; 
	vec2 tileCoords = mod(pixelCoords, tileSize) + 0.5; // 0.5 offset prevents sampling errors at pixel boundaries
	
	uint index = texelFetch(indexBuffer, int(tileIndices.x + tileIndices.y * mapSize.x)).x;
	uint y = index / tileCount.x;
	uint x = index - y * tileCount.x;
	vec2 texCoords = (vec2(x * tileSize.x, y * tileSize.y) + tileCoords) / textureSize(tileTexture, 0);

	FragColor = texture(tileTexture, texCoords);
}