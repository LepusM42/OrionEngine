#version 460
in vec2 vertexTexture;
in vec3 position;
in vec3 baseColor;
uniform vec3 posVec;
uniform mat4x4 gWorld;
uniform mat4x4 transMat;
out vec2 texCoord;
out vec4 color;
void main()
{
	gl_Position = gWorld * transMat * vec4(position.x, position.y, position.z, 1.0);
	gl_Position += posVec;
	color.xyz = baseColor;
	texCoord = vertexTexture;
}