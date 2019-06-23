package com.gg.test;

public class Jni {

    public static void setListener(Listener listener) {
        Jni.listener = listener;
    }

    private static Listener listener;
    private static int hours = 0,minute = 0,second = 0;

    static {
        System.loadLibrary("native-lib");
    }

    public static native String stringFromJNI();

    public static native void startTicker();

    public static native void stopTicker();
//    public void time(){
//        second++;
//        if (second > 60){
//            minute++;
//            second-=60;
//            if (minute > 60){
//                hours++;
//                minute-=60;
//            }
//        }
//        listener.time(hours+":"+minute+":"+second);
//    }
}
