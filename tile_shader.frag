#version 330 core
out vec4 FragColor;

uniform uvec2 screenSize;
uniform uvec2 worldCoords;
uniform usamplerBuffer indexBuffer;
uniform sampler2D tileTexture;

//layout (row_major, std140) uniform tiles // std140 pads arrays to vec4
layout (shared) uniform tiles
{
	uvec4 [380] tileMap;
};

void main()
{
// TEMP, set these via uniform.
	uvec2 tileSize = uvec2(16u, 16u);
	uvec2 tileCount = uvec2(textureSize(tileTexture, 0)) / tileSize;
	uvec2 tileMapCount = uvec2(20u, 19u); // Tilemap dimensions
	
	uvec2 pixelCoords = worldCoords + uvec2(gl_FragCoord.xy); // world space coords, cast negates mid-pixel offset
	uvec2 tileIndices = pixelCoords / tileSize; // Ok. Pass into lookup
	vec2 tileCoords = mod(pixelCoords, tileSize) + 0.5; // 0.5 offset to prevent sampling errors at pixel boundaries
	
	//unsigned int x = 131075u;
	//uvec2 test = uvec2(x >> 16, x & 0xffffu); // Avoid implicit casts for bitwise operators or shader will fail to compile

	// Tile index stored in tilemap
	//uint index = tileMap[tileIndices.x + tileIndices.y * tileMapCount.x].z;
	uint index = texelFetch(indexBuffer, int(tileIndices.x + tileIndices.y * tileMapCount.x)).x;
	uint y = index / tileCount.x;
	uint x = index - y * tileCount.x;
	vec2 texCoords = (vec2(x * tileSize.x, y * tileSize.y) + tileCoords) / textureSize(tileTexture, 0);

	// Texture coords stored in tilemap
	//vec2 tileMapCoords = tileMap[tileIndices.x + tileIndices.y * tileMapCount.x].xy;
	//vec2 texCoords = (tileMapCoords + tileCoords) / textureSize(tileTexture, 0);

	FragColor = texture(tileTexture, texCoords);
}