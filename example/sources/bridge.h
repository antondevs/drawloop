#ifndef __BRIDGE_H
#define __BRIDGE_H

#if defined(_WIN32)
 #define DLAPI __declspec(dllexport)
#elif defined(_WIN32)
 #define DLAPI __declspec(dllimport)
#elif defined(__GNUC__)
 #define DLAPI __attribute__((visibility("default")))
#else
 #define DLAPI
#endif

#ifdef __cplusplus
extern "C" {
#endif

    DLAPI void dlCreateApplication(void);
    DLAPI void dlDrawFrame(void);
    DLAPI void dlTouchDown(int x, int y);
    DLAPI void dlTouchMove(int x, int y);
    DLAPI void dlTouchUp(int x, int y);
    DLAPI void dlUpdateContext(void *context);
    DLAPI void dlUpdateSize(int width, int height);

#ifdef __cplusplus
}
#endif


#endif
