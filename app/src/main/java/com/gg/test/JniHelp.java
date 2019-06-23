package com.gg.test;

import android.os.Build;
import android.support.annotation.Keep;
import android.util.Log;

public class JniHelp {
    private static final String TAG = "JniHelp";
    public void upDataStatus(String var0){
        if (var0.toLowerCase().contains("error")){
            Log.d(TAG,"Native Error->"+var0);
        }else {
            Log.d(TAG,"Native Msg->"+var0);
        }
    }
    @Keep
    public static String getBuildVersion(){
        return Build.VERSION.RELEASE;
    }
    @Keep
    public long getRuntimeSize(){
        return Runtime.getRuntime().freeMemory();
    }
}
