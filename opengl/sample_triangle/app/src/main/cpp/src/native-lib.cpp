#include <jni.h>
#include <string>
#include "../include/MyGLRenderContext.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_yuhb_sample_triangle_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}extern "C"
JNIEXPORT void JNICALL
Java_com_yuhb_sample_triangle_MyNativeRenderer_native_1onSurfaceCreated(JNIEnv *env, jobject thiz) {
    MyGLRenderContext::getInstance()->OnSurfaceCreated();
}

extern "C"
JNIEXPORT void JNICALL
Java_com_yuhb_sample_triangle_MyNativeRenderer_native_1onSurfaceChanged(JNIEnv *env, jobject thiz,
                                                                        jint width, jint height) {
    MyGLRenderContext::getInstance()->OnSurfaceChanged(width,height);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_yuhb_sample_triangle_MyNativeRenderer_native_1onDrawFrame(JNIEnv *env, jobject thiz) {
    MyGLRenderContext::getInstance()->OnDrawFrame();
}extern "C"
JNIEXPORT void JNICALL
Java_com_yuhb_sample_triangle_MyNativeRenderer_native_1destroy(JNIEnv *env, jobject thiz) {
    MyGLRenderContext::getInstance()->destroy();
}