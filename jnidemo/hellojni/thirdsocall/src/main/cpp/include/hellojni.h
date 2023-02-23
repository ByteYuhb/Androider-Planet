//
// Created by Administrator on 2023/2/22.
//
#include <jni.h>
#ifndef HELLO_JNI_HELLOJNI_H
#define HELLO_JNI_HELLOJNI_H

#ifdef __cplusplus
extern "C" {
#endif
    void callJavaField(JNIEnv* env,jobject obj,jstring className,jstring fieldName);
    jboolean callJavaMethod(JNIEnv* env,jobject obj1,jstring className,jstring methodName);
 //HELLO_JNI_HELLOJNI_H
#ifdef __cplusplus
};
#endif

#endif
