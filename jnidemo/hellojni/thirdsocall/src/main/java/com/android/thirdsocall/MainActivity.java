package com.android.thirdsocall;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("third-call-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        callThirdSoMethod("com/android/thirdsocall/HelloCallBack","updateName");
    }
    public native String callThirdSoMethod(String className,String methodName);
}