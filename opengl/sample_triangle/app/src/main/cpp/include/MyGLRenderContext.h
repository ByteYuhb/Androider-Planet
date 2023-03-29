//
// Created by Administrator on 2023/3/29.
//

#ifndef OPENGGL_SAMPLE_TRIANGLE_MYGLRENDERCONTEXT_H
#define OPENGGL_SAMPLE_TRIANGLE_MYGLRENDERCONTEXT_H

#include <GLES3/gl3.h>
#include <jni.h>

class MyGLRenderContext {
    MyGLRenderContext(){

    };
    ~MyGLRenderContext(){
        if(context!= nullptr){
            delete context;
            context = nullptr;
        }
    };
public:
    void OnSurfaceCreated();
    void OnSurfaceChanged(int width,int height);
    void OnDrawFrame();
    void beforeDraw();
    void destroy();

    static MyGLRenderContext* getInstance();

private:
    static MyGLRenderContext* context;
    int mScreenWidth;
    int mScreenHeight;
    GLuint programObj;
    GLuint VAO;
};


#endif //OPENGGL_SAMPLE_TRIANGLE_MYGLRENDERCONTEXT_H
