#version 330 core
out vec4 FragColor;

uniform uvec2 screenSize;
uniform uvec2 worldCoords;
uniform sampler2D tileTexture;

//layout (std140) uniform tiles // std140 pads float to vec4
layout (shared) uniform tiles
{
	uvec2 [380] tileMap;
};

void main()
{
// TEMP, set these via uniform.
	uvec2 tileSize = uvec2(16u, 16u);
	//vec2 tileScale = vec2(2.0, 2.0); // Do scaling in screen shader?

	uvec2 pixelCoords = worldCoords + uvec2(gl_FragCoord.xy); // world space coords, cast negates mid-pixel offset
	uvec2 tileIndices = pixelCoords / tileSize; // Ok. Pass into lookup

	vec2 tileCoords = mod(pixelCoords, tileSize) + 0.5; // 0.5 offset to prevent sampling errors at pixel boundaries
	vec2 texCoords = (tileMap[tileIndices.x + tileIndices.y * 20u] + tileCoords) / textureSize(tileTexture, 0);

	FragColor = texture(tileTexture, texCoords);
}