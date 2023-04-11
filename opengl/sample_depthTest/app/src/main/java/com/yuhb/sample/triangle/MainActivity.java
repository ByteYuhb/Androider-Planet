package com.yuhb.sample.triangle;

import androidx.annotation.NonNull;
import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.content.pm.PackageManager;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.os.Bundle;
import android.view.ViewGroup;
import android.view.ViewTreeObserver;
import android.widget.RelativeLayout;
import android.widget.TextView;

import java.security.Permission;

public class MainActivity extends AppCompatActivity implements ViewTreeObserver.OnGlobalLayoutListener{
    ViewGroup rootView;
    MyGLSurfaceView glSurfaceView;
    MyGLSurfaceRenderer glSurfaceRenderer = new MyGLSurfaceRenderer(this);
    String[] permissions = new String[]{"android.permission.WRITE_EXTERNAL_STORAGE","android.permission.READ_EXTERNAL_STORAGE"};
    @RequiresApi(api = Build.VERSION_CODES.M)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        rootView = findViewById(R.id.root_view);
        rootView.getViewTreeObserver().addOnGlobalLayoutListener(this);
        for(String per:permissions){
            if(ActivityCompat.checkSelfPermission(this,per) != PackageManager.PERMISSION_GRANTED){
                if(Build.VERSION.SDK_INT>=Build.VERSION_CODES.M){
                    requestPermissions(permissions,100);
                }
                return;
            }
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        if(requestCode == 100){
            if(grantResults[0] == PackageManager.PERMISSION_GRANTED){
                glSurfaceView.setmRenderer(glSurfaceRenderer);
            }
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        glSurfaceRenderer.destroy();
    }

    @Override
    public void onGlobalLayout() {
        rootView.getViewTreeObserver().removeOnGlobalLayoutListener(this);
        RelativeLayout.LayoutParams lp = new RelativeLayout.LayoutParams(
                ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
        lp.addRule(RelativeLayout.CENTER_IN_PARENT);
        glSurfaceView = new MyGLSurfaceView(this);
        rootView.addView(glSurfaceView, lp);
        glSurfaceView.setmRenderer(glSurfaceRenderer);
    }
}