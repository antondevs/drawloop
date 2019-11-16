package com.engune.example;

import android.opengl.GLSurfaceView;
import android.os.Build;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    private GLSurfaceView glSurfaceView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        glSurfaceView = new GLSurfaceView(this);

        if (isProbablyEmulator()) {
            glSurfaceView.setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        }

        glSurfaceView.setEGLContextClientVersion(2);
        glSurfaceView.setRenderer(new AppRender());
        setContentView(glSurfaceView);

        getSupportActionBar().hide();
    }

    private boolean isProbablyEmulator() {
        return Build.FINGERPRINT.startsWith("generic") || Build.FINGERPRINT.startsWith("unknown") ||
                Build.MODEL.contains("google_sdk") || Build.MODEL.contains("Emulator") ||
                Build.MODEL.contains("Android SDK built for x86");
    }

    @Override
    protected void onPause() {
        super.onPause();
        glSurfaceView.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();
        glSurfaceView.onResume();
        glSurfaceView.setPreserveEGLContextOnPause(true);
    }

}
