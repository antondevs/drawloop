package com.engune.example;

public class AppLib {

    static {
        System.loadLibrary("applib");
    }

    public static native void nativeOnSurfaceCreate();
    public static native void nativeOnSurfaceUpdate(int width, int height);
    public static native void nativeOnRender();

}
