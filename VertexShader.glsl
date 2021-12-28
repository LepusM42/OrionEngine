#version 460
in vec3 position;
uniform vec3 posVec;
uniform mat4x4 gWorld;
uniform mat4x4 transMat;
out vec4 color;
void main()
{
	gl_Position = gWorld * transMat * vec4(position.x, position.y, position.z, 1.0);
	gl_Position += posVec;
	color = gl_Position;
}