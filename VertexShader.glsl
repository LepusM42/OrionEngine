#version 460
in vec3 position;
uniform float scale;
uniform mat4x4 gWorld;
void main()
{
	gl_Position = gWorld * vec4(position.x*.5, position.y*.5, position.z, 1.0);
}