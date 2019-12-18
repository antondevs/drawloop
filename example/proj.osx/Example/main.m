#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_COCOA
#import <Metal/Metal.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#import <QuartzCore/CAMetalLayer.h>

#import "bridge.h"
#import "nanovg.h"
#import "nanovg_mtl.h"

static void keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

static void windowResizeCallback(GLFWwindow* window, int width, int height)
{
    dlUpdateSize(width, height);
}

int main(void)
{
    const id<MTLDevice> gpu = MTLCreateSystemDefaultDevice();
    const id<MTLCommandQueue> queue = [gpu newCommandQueue];
    CAMetalLayer *swapchain = [CAMetalLayer layer];
    swapchain.device = gpu;
    swapchain.opaque = YES;

    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow *window = glfwCreateWindow(640, 480, "Draw Loop", NULL, NULL);
    NSWindow *nswindow = glfwGetCocoaWindow(window);
    nswindow.contentView.layer = swapchain;
    nswindow.contentView.wantsLayer = YES;

    glfwSetKeyCallback(window, keyboardCallback);
    glfwSetWindowSizeCallback(window, windowResizeCallback);
    
    MTLClearColor color = MTLClearColorMake(1, 1, 1, 1);
    
    NVGcontext* context = nvgCreateMTL((__bridge void *)(swapchain), NVG_ANTIALIAS | NVG_STENCIL_STROKES);
    
    dlCreateApplication();
    dlUpdateContext(context);
    dlUpdateSize(640, 480);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        @autoreleasepool {
            id<CAMetalDrawable> surface = [swapchain nextDrawable];

            MTLRenderPassDescriptor *pass = [MTLRenderPassDescriptor renderPassDescriptor];
            pass.colorAttachments[0].clearColor = color;
            pass.colorAttachments[0].loadAction  = MTLLoadActionClear;
            pass.colorAttachments[0].storeAction = MTLStoreActionStore;
            pass.colorAttachments[0].texture = surface.texture;

            /*id<MTLCommandBuffer> buffer = [queue commandBuffer];
            id<MTLRenderCommandEncoder> encoder = [buffer renderCommandEncoderWithDescriptor:pass];
            
            [encoder endEncoding];
            [buffer presentDrawable:surface];
            [buffer commit];*/
            
            id<MTLCommandBuffer> buffer = [queue commandBuffer];
            dlDrawFrame();
            [buffer presentDrawable:surface];
            [buffer commit];
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
