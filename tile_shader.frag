#version 330 core
out vec4 FragColor;

uniform uvec2 worldCoords;
uniform usamplerBuffer indexBuffer;
uniform sampler2D tileTexture;

layout (std140) uniform tileData
{
	uvec2 screenSize;
	uvec2 tileSize;
	uvec2 tileCount;
	uvec2 mapSize;
};

void main()
{	
	uvec2 pixelCoords = worldCoords + uvec2(gl_FragCoord.xy); // gl_FragCoord gives pixel midpoint
	uvec2 tileIndices = pixelCoords / tileSize; 
	vec2 tileCoords = mod(pixelCoords, tileSize) + 0.5; // 0.5 offset prevents sampling errors at pixel boundaries
	
	uint index = texelFetch(indexBuffer, int(tileIndices.x + tileIndices.y * mapSize.x)).x;
	uint y = index / tileCount.x;
	uint x = index - y * tileCount.x;
	vec2 texCoords = (vec2(x * tileSize.x, y * tileSize.y) + tileCoords) / textureSize(tileTexture, 0);

	FragColor = texture(tileTexture, texCoords);
}