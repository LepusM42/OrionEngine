#version 460
in vec3 position;
uniform float scale;
void main()
{
	gl_Position = vec4(position.x*.5, position.y*scale, position.z, 1.0);
}