package com.android.hellojni;

import android.util.Log;

public class HelloCallBack {
    String name = "HelloCallBack";

    void updateName(String name) throws Exception {
        this.name = name;
        Log.d("HelloJni","你成功调用了HelloCallBack的方法：updateName");
        throw new Exception("dead");
    }
}
