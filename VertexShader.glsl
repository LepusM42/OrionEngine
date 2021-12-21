#version 460
in vec3 position;
uniform float scale;
uniform mat4x4 gWorld;
out vec4 color;
void main()
{
	color = vec4(1.0, 1.0, 1.0, 1.0);
	gl_Position = gWorld * vec4(position.x*scale, position.y*scale, position.z*scale, 1.0);
}