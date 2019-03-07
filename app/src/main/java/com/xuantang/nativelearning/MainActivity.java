package com.xuantang.nativelearning;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        System.loadLibrary("JNIDemo");

        final TextView textView = findViewById(R.id.text);

        JNIDemo jniDemo = new JNIDemo();
        textView.setText(jniDemo.stringFromNative(" Java"));

        final Env env = JNIDemo.create();
        textView.setText(env.sayHello());
        jniDemo.changeName(env, "Change name----------");

        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        textView.setText(env.sayHello());
                    }
                });
            }
        }).start();
    }
}
