// Flat Color Shader

#type vertex
#version 450

layout(location = 0) in vec3 a_Position;

uniform mat4 u_Projection;
uniform mat4 u_View;
uniform mat4 u_Model;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * vec4( a_Position, 1.0 );
    // gl_Position = vec4( a_Position, 1.0 );
}

#type fragment
#version 450

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main()
{
	color = u_Color;
}