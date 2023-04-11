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
const char* shaderSingleColor = (const char *) "#version 300 es \n"
                                               "precision mediump float;\n"
                                               "out vec4 outColor;\n"
                                                     "void main()"
                                                     "{ \n"
                                                     "   outColor = vec4(0.23f, 0.35f, 0.2f, 1.0f); \n"
                                                     "} \n";
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
    singleColorShader = GLUtils::CreateProgram(vShaderStr,shaderSingleColor);
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


void MyGLRenderContext::setCordder(glm::mat4 &model){
    glm::vec3 eye = glm::vec3(0.0f,0.0f,3.0f);
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

        glUniform1i(glGetUniformLocation(programObj,"textureColor"),0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D,textureID);

    }
}
glm::mat4 model,modelScale;
bool isFirstDraw = true;
void MyGLRenderContext::OnDrawFrame() {
    isDrawing = true;
    beforeDraw();
    if(programObj == 0){
        return;
    }
    //清除buffer
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);


    glStencilFunc(GL_ALWAYS,1,0xff);
    glStencilMask(0xff);

    //使用程序着色器对象
    glUseProgram(programObj);
    //绑定VAO
    glBindVertexArray(VAO);
    //观察者位置

    setCordder(model);
    //开始绘制
    glDrawArrays(GL_TRIANGLES,0,36);
    //解绑VAO
    glBindVertexArray(GL_NONE);

    glStencilFunc(GL_NOTEQUAL,1,0xff);
    glStencilMask(0x00);
    glDisable(GL_DEPTH_TEST);

    glUseProgram(singleColorShader);
    glBindVertexArray(VAO);
    GLfloat scale = 1.1f;
    if(isFirstDraw){
        modelScale = glm::scale(modelScale, glm::vec3(scale, scale, scale));
        isFirstDraw = false;
    }
    setCordder(modelScale);

    glDrawArrays(GL_TRIANGLES,0,36);

    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 0, 0xFF);
    glEnable(GL_DEPTH_TEST);
    glBindVertexArray(GL_NONE);
    //解绑程序着色器对象
    glUseProgram(GL_NONE);
    isDrawing = false;
}
void MyGLRenderContext::destroy() {
    if(programObj){
        programObj = GL_NONE;
    }
    glDeleteVertexArrays(1,&VAO);
}

