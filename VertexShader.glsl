#version 460
in vec3 position;
uniform mat4x4 gWorld;
uniform mat4x4 transMat;
out vec4 color;
void main()
{
	gl_Position = gWorld * transMat * vec4(position.x, position.y, position.z, 1.0);
	color = vec4(1.0, 1.0, 1.0, 1.0);
}