package com.yuhb.sample.triangle;

import android.content.Context;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MyGLSurfaceRenderer implements GLSurfaceView.Renderer {
    int rendererMode = GLSurfaceView.RENDERMODE_CONTINUOUSLY;
    MyNativeRenderer nativeRenderer;
    Context mContext;
    MyGLSurfaceRenderer(Context context){
        nativeRenderer = new MyNativeRenderer();
        mContext = context;
    }
    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
        nativeRenderer.native_onSurfaceCreated();
        nativeRenderer.native_init(readStringFromAssets("cube.vsh"),readStringFromAssets("cube.fsh"));
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
        mContext = null;
    }
    public void move(float moveX,float moveY){
        nativeRenderer.native_moveStep(moveX,moveY);
    }

    private String readStringFromAssets(String filePath) {
        //通过设备管理对象 获取Asset的资源路径
        AssetManager assetManager = mContext.getApplicationContext().getAssets();

        InputStream inputStream = null;
        InputStreamReader isr = null;
        BufferedReader br = null;

        StringBuffer sb =  new StringBuffer();
        try{
            inputStream = assetManager.open(filePath);
            isr = new InputStreamReader(inputStream);
            br = new BufferedReader(isr);

            sb.append(br.readLine());
            String line = null;
            while((line = br.readLine()) != null){
                sb.append("\n" + line);
            }

            br.close();
            isr.close();
            inputStream.close();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                if (br != null) {
                    br.close();
                }
                if (isr != null) {
                    isr.close();
                }
                if (inputStream != null) {
                    inputStream.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        return sb.toString();
    }
}
