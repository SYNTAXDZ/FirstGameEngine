// Basic Texture Shader

#type vertex
#version 450

layout(location = 0) in vec3 a_Position;
layout( location = 1 ) in vec3 a_Normal;
layout(location = 2 ) in vec2 a_TexCoord;
uniform mat4 u_View;
uniform mat4 u_Projection;
uniform mat4 u_Model;

out vec3 v_Normal;
out vec2 v_TexCoord;

void main()
{
    v_Normal = a_Normal;
    v_TexCoord = a_TexCoord;
    gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0);
}

#type fragment
#version 450

layout(location = 0) out vec4 color;

in vec3 v_Normal;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main()
{
	color = texture( u_Texture, v_TexCoord );
}
