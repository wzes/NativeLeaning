package com.xuantang.nativelearning;

import androidx.annotation.Nullable;

public class Env {
    public Env() {

    }

    @Override
    public boolean equals(@Nullable Object obj) {
        return super.equals(obj);
    }

    private String name = "Hello";

    public String sayHello() {
       return name;
    }

    public void changeName(String name) {
        this.name = name;
    }
}
