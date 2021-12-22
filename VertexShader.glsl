#version 460
in vec3 position;
uniform vec3 scale;
uniform mat4x4 gWorld;
out vec4 color;
void main()
{
	color = vec4(1.0, 1.0, 1.0, 1.0);
	//gl_Position = gWorld * vec4(position.x, position.y*scale.y, position.z*scale.z, 1.0);
	gl_Position.x = position.x;
	gl_Position.y = position.y * scale.y;
	gl_Position.z = position.z;
	gl_Position.w = 1.0;
}