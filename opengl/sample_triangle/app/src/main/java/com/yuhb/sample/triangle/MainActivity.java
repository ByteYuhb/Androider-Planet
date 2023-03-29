package com.yuhb.sample.triangle;

import androidx.annotation.NonNull;
import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;

import android.content.pm.PackageManager;
import android.opengl.GLSurfaceView;
import android.os.Build;
import android.os.Bundle;
import android.widget.TextView;

import java.security.Permission;

public class MainActivity extends AppCompatActivity {
    MyGLSurfaceView glSurfaceView;
    MyGLSurfaceRenderer glSurfaceRenderer = new MyGLSurfaceRenderer();
    String[] permissions = new String[]{"android.permission.WRITE_EXTERNAL_STORAGE","android.permission.READ_EXTERNAL_STORAGE"};
    @RequiresApi(api = Build.VERSION_CODES.M)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        glSurfaceView = findViewById(R.id.id_surface);
        for(String per:permissions){
            if(ActivityCompat.checkSelfPermission(this,per) != PackageManager.PERMISSION_GRANTED){
                if(Build.VERSION.SDK_INT>=Build.VERSION_CODES.M){
                    requestPermissions(permissions,100);
                }
                return;
            }
        }
        glSurfaceView.setmRenderer(glSurfaceRenderer);

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
}