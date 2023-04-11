#version 300 es
precision mediump float;
in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

out vec4 fragColor;
uniform sampler2D textureColor;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
   vec3 _texture = vec3(texture(textureColor,TexCoord));
   fragColor = vec4(_texture, 1.0f);
}