//
// Created by Administrator on 2023/3/29.
//

#include <GLUtils.h>
#include "../include/MyGLRenderContext.h"
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
    //0.初始化顶点数据
    GLfloat vertices[] = {
            0.0f, 0.5f, 0.0f,1.0f,0.0f,0.0f,
            -0.5f,-0.5f, 0.0f,0.0f,1.0f,0.0f,
            0.5f, -0.5f, 0.0f,0.0f,0.0f,1.0f
    };
    //1.创建着色器程序，此处将着色器程序创建封装到一个工具类中
    char vShaderStr[] =
            "#version 300 es                          \n"
            "layout(location = 0) in vec4 vPosition;  \n"
            "layout(location = 1) in vec3 vColor;  \n"
            "out vec3 color;  \n"
            "void main()                              \n"
            "{                                        \n"
            "   gl_Position = vPosition;              \n"
            "   color = vColor;              \n"
            "}                                        \n";

    char fShaderStr[] =
            "#version 300 es                              \n"
            "precision mediump float;                     \n"
            "in vec3 color;                          \n"
            "out vec4 fragColor;                          \n"
            "void main()                                  \n"
            "{                                            \n"
            "   fragColor = vec4 (color, 1.0 );  \n"
            "}                                            \n";

    programObj = GLUtils::CreateProgram(vShaderStr,fShaderStr);

    //2.生成VAO,VBO对象,并绑定顶点属性
    GLuint VBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    //顶点坐标属性
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(0);
    //顶点颜色属性
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(GLfloat),(GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(GL_NONE);
}
/**
 * 1.清除buffer
 * 2.使用程序着色器对象
 * 3.开始绘制
 * 4.解绑
 * */
void MyGLRenderContext::OnDrawFrame() {
    beforeDraw();
    if(programObj == 0){
        return;
    }
    //清除buffer
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.3f,0.5f,0.4f,1.0f);
    //使用程序着色器对象
    glUseProgram(programObj);
    //绑定VAO
    glBindVertexArray(VAO);
    //开始绘制
    glDrawArrays(GL_TRIANGLES,0,3);
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

