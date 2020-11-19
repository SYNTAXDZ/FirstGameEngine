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
out vec3 v_FragPos;

void main() {

    v_FragPos = vec3( u_Model * vec4( a_Position, 1.0 ) );
    v_Normal = mat3( transpose( inverse( u_Model ) ) ) * a_Normal;
    v_TexCoord = a_TexCoord;
    gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0);
}

#type fragment
#version 450

layout(location = 0) out vec4 color;

in vec3 v_Normal;
in vec2 v_TexCoord;
in vec3 v_FragPos;

struct Material {

    vec3  ambient;
    vec3  diffuse;
    vec3  specular;
    float shininess;

};
uniform Material material;

struct Light {

    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

};
uniform Light light;

uniform vec3 u_ViewPos;
uniform vec3 u_LightPos;

uniform sampler2D u_Texture;

void main() {

    vec3 normal = normalize( v_Normal );
    vec3 lightDir = normalize( light.position - v_FragPos );
    vec3 viewDir = normalize( u_ViewPos - v_FragPos );
    vec3 reflectDir = reflect( -lightDir, normal );

    float diff = max( dot( normal, lightDir ), 0.0 );
    float spec = pow( max( dot( viewDir, reflectDir ), 0.0 ), material.shininess );
    float ambientStrengh = 0.1;
    float specularStrength = 0.5;

    vec3 ambient = material.ambient * light.ambient;
    vec3 diffuse = ( diff * material.diffuse ) * light.diffuse;
    vec3 specular = ( material.specular * spec ) * light.specular;

    vec3 result = ( ambient + diffuse + specular );

    color = vec4( result, 1.0 );

}
