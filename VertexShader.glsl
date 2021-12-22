#version 460
in vec3 position;
uniform vec3 scale;
uniform mat4x4 gWorld;
uniform mat4x4 transMat;
out vec4 color;
void main()
{
	gl_Position = gWorld * transMat * vec4(position.x, position.y, position.z, 1.0);
	color = vec4(gl_Position.x, gl_Position.y, gl_Position.z, 1.0);
}