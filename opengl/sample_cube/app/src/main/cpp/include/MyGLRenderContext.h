//
// Created by Administrator on 2023/3/29.
//

#ifndef OPENGGL_SAMPLE_TRIANGLE_MYGLRENDERCONTEXT_H
#define OPENGGL_SAMPLE_TRIANGLE_MYGLRENDERCONTEXT_H

#include <GLES3/gl3.h>
#include <jni.h>
#include <LogUtil.h>

class MyGLRenderContext {
    MyGLRenderContext(){
        programObj = GL_NONE;
        VAO = GL_NONE;
        textureID = GL_NONE;
        moveX = 0.0f;
        moveY = 0.0f;
    };
    ~MyGLRenderContext(){
        if(context!= nullptr){
            delete context;
            context = nullptr;
        }
        if(vShaderStr!= nullptr){
            delete vShaderStr;
            vShaderStr = nullptr;
        }
        if(fShaderStr!= nullptr){
            delete fShaderStr;
            fShaderStr = nullptr;
        }
    };
public:
    void init(const char* vShaderStr,const char* fShaderStr){
        this->vShaderStr = vShaderStr;
        this->fShaderStr = fShaderStr;
    }
    void OnSurfaceCreated();
    void OnSurfaceChanged(int width,int height);
    void OnDrawFrame();
    void beforeDraw();
    void destroy();
    void move(float moveStepX,float moveStepY){
        moveX = moveStepX/100000.0f;
        moveY = moveStepY/100000.0f;
        LOGCATD("moveStep:%f",moveY);
    }

    static MyGLRenderContext* getInstance();

private:
    static MyGLRenderContext* context;
    int mScreenWidth;
    int mScreenHeight;
    GLuint programObj;
    GLuint VAO;
    GLuint textureID;

    const char* vShaderStr;
    const char* fShaderStr;
    float moveX,moveY;
};


#endif //OPENGGL_SAMPLE_TRIANGLE_MYGLRENDERCONTEXT_H
