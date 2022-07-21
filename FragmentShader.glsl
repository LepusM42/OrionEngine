#version 460
out vec4 FragColor;
in vec2 texCoord;
in vec4 color;
uniform sampler2D tex;

vec2 uv = vec2(texCoord.x,texCoord.y);
vec4 c = texture(tex, uv);

void main()
{
	FragColor = texture(tex, uv);
}