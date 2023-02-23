package com.android.hellojni;

public class HelloJni {
    static {
        System.loadLibrary("hello-jni");
    }
    public native void callJavaField(String className,String fieldName) ;
    public native boolean callJavaMethod(String className,String methodName) ;
}
