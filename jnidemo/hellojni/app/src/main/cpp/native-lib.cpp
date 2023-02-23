#include <jni.h>
#include <string>
#include "include/hellojni.h"
extern "C" JNIEXPORT jstring JNICALL
Java_com_android_hellojni_MainActivity_stringFromJNI(
        JNIEnv* env,jobject obj,jstring className,jstring fieldName,jstring methodName) {
    std::string hello = "Hello from C++";

    callJavaField(env,obj,className,fieldName);
    callJavaMethod(env,obj,className,methodName);
    return env->NewStringUTF(hello.c_str());
}
