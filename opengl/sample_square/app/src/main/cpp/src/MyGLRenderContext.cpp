//
// Created by Administrator on 2023/3/29.
//

#include <GLUtils.h>
#include "../include/ImageUtil.h"
#include "../include/MyGLRenderContext.h"
#include "../include/LogUtil.h"
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
            //顶点             //纹理坐标
            -0.5f, -0.5f, 0.0f,0.0f, 0.0f,//V0
            0.5f,-0.5f, 0.0f,1.0f,0.0f,//V1
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f,//V2
            -0.5f, 0.5f, 0.0f,0.0f, 1.0f//V3
    };
    //确定三角形索引
    GLint indices[] = {
            0,1,2,
            0,2,3
    };



    //1.创建着色器程序，此处将着色器程序创建封装到一个工具类中
    char vShaderStr[] =
            "#version 300 es                          \n"
            "layout(location = 0) in vec4 vPosition;  \n"
            "layout(location = 1) in vec2 texCords;  \n"
            "out vec2 color;  \n"
            "void main()                              \n"
            "{                                        \n"
            "   gl_Position = vPosition;              \n"
            "   color = texCords;              \n"
            "}                                        \n";

    char fShaderStr[] =
            "#version 300 es                              \n"
            "precision mediump float;                     \n"
            "in vec2 color;                          \n"
            "out vec4 fragColor;                          \n"
            "uniform sampler2D textureColor;                          \n"
            "void main()                                  \n"
            "{                                            \n"
            "   vec3 picColor = vec3 (texture(textureColor,color));  \n"
            "   fragColor = vec4 (picColor, 1.0 );  \n"
            "}                                            \n";

    programObj = GLUtils::CreateProgram(vShaderStr,fShaderStr);

    //2.生成VAO,VBO对象,并绑定顶点属性
    GLuint VBO,EBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);

    //顶点坐标属性
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),(GLvoid*)0);
    glEnableVertexAttribArray(0);
    //顶点颜色属性
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),(GLvoid*)(3*sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

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
void MyGLRenderContext::OnDrawFrame() {
    beforeDraw();
    if(programObj == 0){
        return;
    }
    //清除buffer
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.3f,0.5f,0.4f,1.0f);

    glUniform1i(glGetUniformLocation(programObj, "textureColor"), 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    //使用程序着色器对象
    glUseProgram(programObj);
    //绑定VAO
    glBindVertexArray(VAO);
    //开始绘制
    //glDrawArrays(GL_TRIANGLES,0,6);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
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

