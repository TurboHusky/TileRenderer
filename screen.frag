#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform vec2 offset;
uniform sampler2D screenTexture;

void main()
{
	FragColor = texture(screenTexture, vec2((TexCoords.x + offset.x), (TexCoords.y + offset.y)));
}