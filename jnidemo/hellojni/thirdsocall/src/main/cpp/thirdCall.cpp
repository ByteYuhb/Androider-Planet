#include <jni.h>
#include <string>
//#include "include/hellojni.h"
#include <hellojni.h>



extern "C" JNIEXPORT jstring JNICALL
Java_com_android_thirdsocall_MainActivity_callThirdSoMethod(
        JNIEnv* env,
        jobject obj,jstring className,jstring methodName) {

    std::string hello = "hello c++";
    callJavaMethod(env,obj,className,methodName);

    return env->NewStringUTF(hello.c_str());
}