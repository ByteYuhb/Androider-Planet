#version 300 es
precision mediump float;
in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

out vec4 fragColor;
uniform vec3 viewPos;
struct Light
{
   vec3 position;
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
   /*衰减
   constant:常数项
   linear：一次项
   quadratic：二次项
   衰减值 = 1.0f/constant+linear*distance+quadratic*distance*distance;

   灯光亮度要减去当前衰减值
   */
   float constant;
   float linear;
   float quadratic;
};
uniform Light light;

struct Material
{
//漫反射光照下物体颜色
   sampler2D diffuse;
//反射一个物体特定的镜面高光颜色
   sampler2D specular;
//放射光贴图
   sampler2D emission;
//影响镜面高光的散射/半径 如2,4,8,16,32,64,128,256
   float shininess;
};
uniform Material material;
void main()
{

   //设置环境光照
   vec3 ambient = light.ambient * vec3(texture(material.diffuse,TexCoord));
   /*
   设置慢反射光照
   1.定向光方向固定
   2.使用1中获取的片段到灯源的向量和法向量的点乘，可以获取夹角大小的cos值，如果cos值越大，说明夹角越小，当前片段的光越亮
   */
   vec3 norm = normalize(Normal);
   vec3 lightDir = normalize(light.position-FragPos);
   float diff = max(dot(norm,lightDir),0.0f);
   vec3 diffuse = light.diffuse*diff*vec3(texture(material.diffuse,TexCoord));

   /*
   设置镜面高光
   1.计算片段到观察者的向量：使用viewPos-FragPos得到
   2.计算灯源的反射向量，使用reflect得到
   3.获取1和2向量的夹角的cos值，cos值越大，夹角越小，光线越强烈
   */
   //1
   vec3 viewDir = normalize(viewPos-FragPos);
   //2
   vec3 reflectDir = reflect(-lightDir,norm);
   //3
   float spec = pow(max(dot(viewDir,reflectDir),0.0f),material.shininess);
   vec3 specular = light.specular*spec*vec3(texture(material.specular,TexCoord));

   /*
   计算衰减值
   */
   float distance = length(light.position-FragPos);
   float attenuation = 1.0f/(light.constant+light.linear*distance+light.quadratic*distance*distance);

   vec3 result = (ambient+diffuse+specular)*attenuation;
   fragColor = vec4(result, 1.0f);
}