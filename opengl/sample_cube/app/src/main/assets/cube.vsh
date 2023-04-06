#version 300 es
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 normals;
layout(location = 2) in vec2 texCords;

out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
   gl_Position = projection*view*model*vec4(vPosition,1.0f);
   TexCoord = texCords;
   Normal = mat3(transpose(inverse(model)))*normals;
   FragPos = vec3(model*vec4(vPosition,1.0f));
}