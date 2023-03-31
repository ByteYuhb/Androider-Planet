package com.yuhb.sample.triangle;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;


public class MyGLSurfaceView extends GLSurfaceView {

    Renderer mRenderer;
    public MyGLSurfaceView(Context context) {
        this(context,null);
    }

    public MyGLSurfaceView(Context context, AttributeSet attrs) {
        super(context, attrs);
        setEGLContextClientVersion(2);
        setEGLConfigChooser(8,8,8,8,16,8);
    }

    public void setmRenderer(MyGLSurfaceRenderer mRenderer) {
        this.mRenderer = mRenderer;
        setRenderer(mRenderer);
        setRenderMode(mRenderer.rendererMode);
    }

}
