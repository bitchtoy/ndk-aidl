package com.gg.test;

import android.annotation.SuppressLint;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity{

    // Used to load the 'native-lib' library on application startup.

    private TextView tv,tm;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        tv = findViewById(R.id.sample_text);
        tm = findViewById(R.id.time_text);
//        tv.setText(stringFromJNI());
        tm.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Jni.startTicker();
            }
        });


    }

    private int hours = 0,minute = 0,second = 0;


    public void time(){
        second++;
        if (second > 60){
            minute++;
            second-=60;
            if (minute > 60){
                hours++;
                minute-=60;
            }
        }

        Log.d("------->",hours+":"+minute+":"+second);
//        runOnUiThread(new Runnable() {
//            @Override
//            public void run() {
//
//                    tm.setText(hours+":"+minute+":"+second);
//
//
//            }
//        });
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    @Override
    protected void onDestroy() {
        super.onDestroy();
        Jni.stopTicker();
    }

//    @Override
//    public void time(String a) {
//        tm.setText(a);
//    }
}
