package com.yuhb.sample.triangle;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.util.Log;
import android.view.MotionEvent;


public class MyGLSurfaceView extends GLSurfaceView {

    MyGLSurfaceRenderer mRenderer;
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
    float lastX = 0,lastY = 0;
    @Override
    public boolean onTouchEvent(MotionEvent event) {
        int action = event.getAction();
        float dx = 0,dy = 0;
        float curX = event.getX();
        float curY = event.getY();
        switch (action){
            case MotionEvent.ACTION_DOWN:
                lastX = curX;
                lastY = curY;
                 break;

            case MotionEvent.ACTION_MOVE:
                dx = curX-lastX;
                dy = curY-lastY;
                mRenderer.move(dx,dy);
                lastX = curX;
                lastY = curY;
                 break;
            case MotionEvent.ACTION_UP:
                mRenderer.move(0.0f,0.0f);
                 break;
        }
        Log.d("MyGLSurfaceView","curX:"+curX+" curY:"+curY);
        Log.d("MyGLSurfaceView","dx:"+dx+" dy:"+dy);
        return true;

    }
}
