package com.android.hellojni;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        //tv.setText(stringFromJNI("com/android/hellojni/HelloCallBack","name","updateName"));
        HelloJni jni = new HelloJni();

        tv.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try{
                    jni.callJavaField("com/android/hellojni/HelloCallBack","namesss");
                    jni.callJavaMethod("com/android/hellojni/HelloCallBack","updateName");
                }catch (Exception e){
                    e.printStackTrace();
                    return;
                }
            }
        });

    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI(String className,String fieldName,String methodName);
}