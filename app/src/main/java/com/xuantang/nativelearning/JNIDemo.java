package com.xuantang.nativelearning;

public class JNIDemo {

    public native String stringFromNative(String param);

    public native synchronized static Env create();

    public native String changeName(Env env, String name);
}
