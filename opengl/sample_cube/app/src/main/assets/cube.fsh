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
   //设置环境光照
   float ambientStrength = 0.2f;
   vec3 ambient = ambientStrength * lightColor;
   /*
   设置慢反射光照
   1.先通过灯源pos和片段pos找到片段到灯源的向量：使用lightPos-FragPos
   2.使用1中获取的片段到灯源的向量和法向量的点乘，可以获取夹角大小的cos值，如果cos值越大，说明夹角越小，当前片段的光越亮
   */
   vec3 norm = normalize(Normal);
   vec3 lightDir = normalize(lightPos-FragPos);
   float diff = max(dot(norm,lightDir),0.0f);
   vec3 diffuse = diff*lightColor;

   /*设置镜面高光
   1.计算片段到观察者的向量：使用viewPos-FragPos得到
   2.计算灯源的反射向量，使用reflect得到
   3.获取1和2向量的夹角的cos值，cos值越大，夹角越小，光线越强烈*/

   float specularStrength = 0.5f;
   //1
   vec3 viewDir = normalize(viewPos-FragPos);
   //2
   vec3 reflectDir = reflect(-lightDir,norm);
   //3
   float spec = specularStrength*pow(max(dot(viewDir,reflectDir),0.0f),64.0f);

   vec3 result = (ambient+diffuse+spec)*objectColor;
   fragColor = vec4(result, 1.0f);
}