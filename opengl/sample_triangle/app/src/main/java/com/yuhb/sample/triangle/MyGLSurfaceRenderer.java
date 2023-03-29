package com.yuhb.sample.triangle;

import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MyGLSurfaceRenderer implements GLSurfaceView.Renderer {
    int rendererMode = GLSurfaceView.RENDERMODE_CONTINUOUSLY;
    MyNativeRenderer nativeRenderer;
    MyGLSurfaceRenderer(){
        nativeRenderer = new MyNativeRenderer();
    }
    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
        nativeRenderer.native_onSurfaceCreated();
    }

    @Override
    public void onSurfaceChanged(GL10 gl10, int width, int height) {
        nativeRenderer.native_onSurfaceChanged(width,height);
    }

    @Override
    public void onDrawFrame(GL10 gl10) {
        nativeRenderer.native_onDrawFrame();
    }

    public void destroy(){
        nativeRenderer.native_destroy();
    }
}
