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
Java_com_yuhb_sample_triangle_MyNativeRenderer_native_1init(JNIEnv *env, jobject thiz,
                                                            jstring v_shader_str,
                                                            jstring f_shader_str) {
    jboolean isCopy;
    const char* vShader = env->GetStringUTFChars(v_shader_str,&isCopy);
    const char* fShader = env->GetStringUTFChars(f_shader_str,&isCopy);
    MyGLRenderContext::getInstance()->init(vShader,fShader);
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
}extern "C"
JNIEXPORT void JNICALL
Java_com_yuhb_sample_triangle_MyNativeRenderer_native_1moveStep(JNIEnv *env, jobject thiz,
                                                                jfloat move_stepX,jfloat move_stepY) {
    MyGLRenderContext::getInstance()->move(move_stepX,move_stepY);
}