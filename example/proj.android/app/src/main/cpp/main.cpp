#include <jni.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#define NANOVG_GLES2_IMPLEMENTATION
#include <nanovg.h>
#include <nanovg_gl.h>
#include "../../../../../sources/bridge.h"
#include "../../../../../sources/application.hpp"

AAssetManager *assetManager = nullptr;
struct NVGcontext* context = nullptr;

extern "C" JNIEXPORT void JNICALL Java_com_engune_example_AppLib_nativeOnSurfaceCreate(JNIEnv * env, jclass cls) {
    context = nvgCreateGLES2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
    dlCreateApplication();
    dlUpdateContext(context);
}

extern "C" JNIEXPORT void JNICALL Java_com_engune_example_AppLib_nativeOnSurfaceUpdate(JNIEnv * env, jclass cls, jint width, jint height) {
    dlUpdateSize(width, height);
}

extern "C" JNIEXPORT void JNICALL Java_com_engune_example_AppLib_nativeOnRender(JNIEnv * env, jclass cls) {
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    dlDrawFrame();
}