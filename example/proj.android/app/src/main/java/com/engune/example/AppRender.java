package com.engune.example;

import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class AppRender implements GLSurfaceView.Renderer {
    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        AppLib.nativeOnSurfaceCreate();
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        AppLib.nativeOnSurfaceUpdate(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        AppLib.nativeOnRender();
    }
}
