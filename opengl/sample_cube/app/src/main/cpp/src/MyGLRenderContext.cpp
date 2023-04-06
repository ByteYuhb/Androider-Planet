//
// Created by Administrator on 2023/3/29.
//

#include <GLUtils.h>
#include "../include/ImageUtil.h"
#include "../include/MyGLRenderContext.h"
#include "../include/LogUtil.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
MyGLRenderContext* MyGLRenderContext::context = nullptr;
//单例类
MyGLRenderContext * MyGLRenderContext::getInstance() {
    if(context == nullptr){
        context = new MyGLRenderContext();
    }
    return context;
}

void MyGLRenderContext::OnSurfaceCreated() {
    glClearColor(0.1f,0.2f,0.3f,1.0f);

}

void MyGLRenderContext::OnSurfaceChanged(int width, int height) {
    glViewport(0,0,width,height);
    mScreenWidth = width;
    mScreenHeight = height;
}

/**
 * 绘制前操作
 * 0.初始化顶点数据
 * 1.创建着色器程序对象
 * 2.生成VAO,VBO对象
 * */
void MyGLRenderContext::beforeDraw() {
    if(programObj!= 0){
        return;
    }
    float vertices[] = {
            // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
    };
  /*  //确定三角形索引
    GLint indices[] = {
            0,1,3,
            1,2,3
    };*/

    programObj = GLUtils::CreateProgram(vShaderStr,fShaderStr);

    //2.生成VAO,VBO对象,并绑定顶点属性
    GLuint VBO,EBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
//    glGenBuffers(1,&EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);*/

    //顶点坐标属性
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(0);
    //顶点颜色属性
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    //顶点颜色属性
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(GLfloat),(GLvoid*)(6*sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(GL_NONE);
    //生成纹理
    glGenTextures(1, &textureID);
    ImageUtil::_stbi_set_flip_vertically_on_load(true);
    int width, height, nrComponents;
    unsigned char *data = ImageUtil::_stb_image_load("/sdcard/mmpic.png", &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        ImageUtil::_stb_image_free(data);
    }
    else
    {
        LOGCATE("Texture failed to load at path: %s",data);
        ImageUtil::_stb_image_free(data);
    }

}
/**
 * 1.清除buffer
 * 2.使用程序着色器对象
 * 3.开始绘制
 * 4.解绑
 * */
float iem = 0.0f;
glm::mat4 model;

void MyGLRenderContext::OnDrawFrame() {
    beforeDraw();
    if(programObj == 0){
        return;
    }
    //清除buffer
    //glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    GLuint txID = GL_TEXTURE0;
    GLuint txValue = 0;

    //使用程序着色器对象
    glUseProgram(programObj);
    //绑定VAO
    glBindVertexArray(VAO);
    //观察者位置
    glm::vec3 eye = glm::vec3(-1.0f,0.0f,3.0f);
    {

        //缩小y轴,变换视口
        //model = glm::scale(model,glm::vec3((float)mScreenWidth/mScreenHeight,(float)mScreenWidth/mScreenHeight,(float)mScreenWidth/mScreenHeight));
        //model = glm::rotate(model,45.0f,glm::vec3(1.0f,-1.0f,0.0f));
        /**
         * 计算旋转轴
         * 使用两个向量的叉乘可以获取一个垂直这两个向量的新向量
         * 向量V为移动的方向向量vec3(moveX,moveY,0.0f);
         * 向量K为垂直屏幕的向量vec3(0.0f,0.0f,1.0f); 可以使用单位向量代替
         * */
        if(moveX!=0||moveY!=0){
            float radius = 360.0f;
            float moveL = sqrt(moveX*moveX+moveY*moveY);
            LOGCATD("move moveL:%f",moveL);
            glm::vec3 _v = glm::vec3(moveX,moveY,0.0f);
            glm::vec3 _k = glm::vec3(0.0f,0.0f,1.0f);
            glm::vec3 _u = glm::cross(_k,_v);
//            _u = glm::vec3(0.0f,-1.0f,0.0f);
            float angle = sin(moveL)*radius;
            LOGCATD("move angle:%f %f %f",_u.x,_u.y,_u.z);

            model = glm::rotate(model,angle,_u);
        }else {
            model = glm::rotate(model,0.0f,glm::vec3(0.0f,1.0f,0.0f));
        }

        glUniformMatrix4fv(glGetUniformLocation(programObj,"model"),1,GL_FALSE,glm::value_ptr(model));

        glm::mat4 view;
        view = glm::lookAt(eye,glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,1.0f,0.0f));
        glUniformMatrix4fv(glGetUniformLocation(programObj,"view"),1,GL_FALSE,glm::value_ptr(view));

        glm::mat4 projection;
        projection = glm::perspective(45.0f,(GLfloat)mScreenWidth/(GLfloat)mScreenHeight,0.1f,100.0f);
        glUniformMatrix4fv(glGetUniformLocation(programObj,"projection"),1,GL_FALSE,glm::value_ptr(projection));

    }
    //绘制光照
    {
        /*//测试普通光照//环境光照
        //光照的颜色
        glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
        glUniform3f(glGetUniformLocation(programObj,"lightColor"), lightColor.x,lightColor.y,lightColor.z);
        //物体的颜色
        glm::vec3 objectColor = glm::vec3(1.0f, 0.5f, 0.31f);
        glUniform3f(glGetUniformLocation(programObj,"objectColor"),objectColor.x,objectColor.y,objectColor.z);
        //灯源的位置
        glm::vec3 lightPos = glm::vec3(1.0f, 0.2f, 2.0f);
        glUniform3f(glGetUniformLocation(programObj,"lightPos"),lightPos.x,lightPos.y,lightPos.z);
        //观察者位置
        glUniform3f(glGetUniformLocation(programObj,"viewPos"),eye.x,eye.y,eye.z);*/

       /* //测试带纹理的光照:定向光
        struct Light
        {
            glm::vec3 direction;
            glm::vec3 ambient;
            glm::vec3 diffuse;
            glm::vec3 specular;
        };
        Light light;
        light.direction = glm::vec3(0.0f, 0.0f, -1.0f);
        light.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
        light.diffuse = glm::vec3(0.5f, 0.5f, 0.5);
        light.specular = glm::vec3(1.0f, 1.0f, 1.0f);
        // Set lights properties
        glUniform3f(glGetUniformLocation(programObj, "light.direction"),  light.direction.x,light.direction.y,light.direction.z);
        glUniform3f(glGetUniformLocation(programObj, "light.ambient"),  light.ambient.x,light.ambient.y,light.ambient.z);
        glUniform3f(glGetUniformLocation(programObj, "light.diffuse"),  light.diffuse.x,light.diffuse.y,light.diffuse.z);
        glUniform3f(glGetUniformLocation(programObj, "light.specular"), light.specular.x,light.specular.y,light.specular.z);

        struct Material
        {
            //漫反射光照下物体颜色
            GLuint diffuse;
            //反射一个物体特定的镜面高光颜色
            GLuint specular;
            //放射光贴图
            GLuint emission;
            //影响镜面高光的散射/半径 如2,4,8,16,32,64,128,256
            float shininess;
        };
        Material material;
        material.diffuse = textureID;
        material.specular = textureID;
        material.shininess = 64.0f;
        // Set material properties
        glUniform1f(glGetUniformLocation(programObj, "material.shininess"), material.shininess);

        glUniform1i(glGetUniformLocation(programObj,"material.diffuse"),txValue++);
        glActiveTexture(txID++);
        glBindTexture(GL_TEXTURE_2D,material.diffuse);

        glUniform1i(glGetUniformLocation(programObj,"material.specular"),txValue++);
        glActiveTexture(txID++);
        glBindTexture(GL_TEXTURE_2D,material.specular );

        //观察者位置
        glUniform3f(glGetUniformLocation(programObj,"viewPos"),eye.x,eye.y,eye.z);*/

       /* //测试带纹理的光照:点光源
        struct Light
        {
            glm::vec3 position;
            glm::vec3 ambient;
            glm::vec3 diffuse;
            glm::vec3 specular;
            *//*衰减
            constant:常数项
            linear：一次项
            quadratic：二次项
            衰减值 = 1.0f/constant+linear*distance+quadratic*distance*distance;

            灯光亮度要减去当前衰减值*//*

            float constant;
            float linear;
            float quadratic;
        };
        Light light;
        light.position = glm::vec3(0.0f, 1.0f, 0.0f);
        light.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
        light.diffuse = glm::vec3(0.5f, 0.5f, 0.5);
        light.specular = glm::vec3(1.0f, 1.0f, 1.0f);
        light.constant = 1.0;
        light.linear = 0.35;
        light.quadratic = 0.44;
        // Set lights properties
        glUniform3f(glGetUniformLocation(programObj, "light.position"),  light.position.x,light.position.y,light.position.z);
        glUniform3f(glGetUniformLocation(programObj, "light.ambient"),  light.ambient.x,light.ambient.y,light.ambient.z);
        glUniform3f(glGetUniformLocation(programObj, "light.diffuse"),  light.diffuse.x,light.diffuse.y,light.diffuse.z);
        glUniform3f(glGetUniformLocation(programObj, "light.specular"), light.specular.x,light.specular.y,light.specular.z);
        glUniform1f(glGetUniformLocation(programObj,"light.constant"),light.constant);
        glUniform1f(glGetUniformLocation(programObj,"light.linear"),light.linear);
        glUniform1f(glGetUniformLocation(programObj,"light.quadratic"),light.quadratic);

        struct Material
        {
            //漫反射光照下物体颜色
            GLuint diffuse;
            //反射一个物体特定的镜面高光颜色
            GLuint specular;
            //放射光贴图
            GLuint emission;
            //影响镜面高光的散射/半径 如2,4,8,16,32,64,128,256
            float shininess;
        };
        Material material;
        material.diffuse = textureID;
        material.specular = textureID;
        material.shininess = 64.0f;
        // Set material properties
        glUniform1f(glGetUniformLocation(programObj, "material.shininess"), material.shininess);

        glUniform1i(glGetUniformLocation(programObj,"material.diffuse"),txValue++);
        glActiveTexture(txID++);
        glBindTexture(GL_TEXTURE_2D,material.diffuse);

        glUniform1i(glGetUniformLocation(programObj,"material.specular"),txValue++);
        glActiveTexture(txID++);
        glBindTexture(GL_TEXTURE_2D,material.specular );

        //观察者位置
        glUniform3f(glGetUniformLocation(programObj,"viewPos"),eye.x,eye.y,eye.z);*/

        //测试带纹理的光照:聚光光源
        struct Light
        {
            glm::vec3 position;
            //聚光指向的方向
            glm::vec3 direction;
            //夹角的cos值，值大于cutoff说明夹角越小，需要显示聚光，小余，不需要显示聚光
            float cutoff;
            float outerCutoff;

            glm::vec3 ambient;
            glm::vec3 diffuse;
            glm::vec3 specular;
            /*衰减
            constant:常数项
            linear：一次项
            quadratic：二次项
            衰减值 = 1.0f/constant+linear*distance+quadratic*distance*distance;

            灯光亮度要减去当前衰减值*/

            float constant;
            float linear;
            float quadratic;
        };
        Light light;
        light.position = glm::vec3(0.0f, 0.0f, 1.0f);
        light.direction = glm::vec3(0.0f, 0.0f, -1.0f);
        light.cutoff = glm::cos(glm::radians(15.0f));
        light.outerCutoff = glm::cos(glm::radians(20.0f));

        light.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
        light.diffuse = glm::vec3(0.5f, 0.5f, 0.5);
        light.specular = glm::vec3(1.0f, 1.0f, 1.0f);
        light.constant = 1.0;
        light.linear = 0.35;
        light.quadratic = 0.44;
        // Set lights properties
        glUniform3f(glGetUniformLocation(programObj, "light.position"),  light.position.x,light.position.y,light.position.z);
        glUniform3f(glGetUniformLocation(programObj, "light.ambient"),  light.ambient.x,light.ambient.y,light.ambient.z);
        glUniform3f(glGetUniformLocation(programObj, "light.diffuse"),  light.diffuse.x,light.diffuse.y,light.diffuse.z);
        glUniform3f(glGetUniformLocation(programObj, "light.specular"), light.specular.x,light.specular.y,light.specular.z);
        glUniform1f(glGetUniformLocation(programObj,"light.constant"),light.constant);
        glUniform1f(glGetUniformLocation(programObj,"light.linear"),light.linear);
        glUniform1f(glGetUniformLocation(programObj,"light.quadratic"),light.quadratic);

        glUniform3f(glGetUniformLocation(programObj, "light.direction"),  light.direction.x,light.direction.y,light.direction.z);
        glUniform1f(glGetUniformLocation(programObj,"light.cutoff"),light.cutoff);
        glUniform1f(glGetUniformLocation(programObj,"light.outerCutoff"),light.outerCutoff);

        struct Material
        {
            //漫反射光照下物体颜色
            GLuint diffuse;
            //反射一个物体特定的镜面高光颜色
            GLuint specular;
            //放射光贴图
            GLuint emission;
            //影响镜面高光的散射/半径 如2,4,8,16,32,64,128,256
            float shininess;
        };
        Material material;
        material.diffuse = textureID;
        material.specular = textureID;
        material.shininess = 64.0f;
        // Set material properties
        glUniform1f(glGetUniformLocation(programObj, "material.shininess"), material.shininess);

        glUniform1i(glGetUniformLocation(programObj,"material.diffuse"),txValue++);
        glActiveTexture(txID++);
        glBindTexture(GL_TEXTURE_2D,material.diffuse);

        glUniform1i(glGetUniformLocation(programObj,"material.specular"),txValue++);
        glActiveTexture(txID++);
        glBindTexture(GL_TEXTURE_2D,material.specular );

        //观察者位置
        glUniform3f(glGetUniformLocation(programObj,"viewPos"),eye.x,eye.y,eye.z);

    }
    //开始绘制
    //glDrawArrays(GL_TRIANGLES,0,6);
    //glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    //解绑VAO
    glBindVertexArray(GL_NONE);
    //解绑程序着色器对象
    glUseProgram(GL_NONE);
}
void MyGLRenderContext::destroy() {
    if(programObj){
        programObj = GL_NONE;
    }
    glDeleteVertexArrays(1,&VAO);
}

