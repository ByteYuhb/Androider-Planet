package com.yuhb.sample.triangle;

public class MyNativeRenderer {
    static {
        System.loadLibrary("opengl-es-lib");
    }
    public MyNativeRenderer(){

    }
    public native void native_onSurfaceCreated();
    public native void native_onSurfaceChanged(int width,int height);
    public native void native_onDrawFrame();
    public native void native_destroy();

}
