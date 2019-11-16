//
//  AppViewController.m
//  Example
//
//  Created by Developer on 26.10.2019.
//  Copyright © 2019 Developer. All rights reserved.
//

#import "bridge.h"
#import "nanovg.h"
#import "nanovg_mtl.h"
#import "AppViewController.h"

@interface AppViewController ()

@end

@implementation AppViewController {
    NVGcontext *context;
}

@synthesize metalView;
@synthesize commandQueue;

- (void)viewDidLoad {
    [super viewDidLoad];
    
    dlCreateApplication();
    
    id<MTLDevice> device = MTLCreateSystemDefaultDevice();
    metalView = [[MTKView alloc] initWithFrame:CGRectZero device:device];
    commandQueue = [device newCommandQueue];
    metalView.clearColor = MTLClearColorMake(1.0, 1.0, 1.0, 1.0);
    metalView.delegate = self;
    [self.view addSubview:metalView];
    
    context = nvgCreateMTL((__bridge void *)(metalView.layer), NVG_ANTIALIAS | NVG_STENCIL_STROKES);
    dlUpdateContext(context);
}

- (void)viewDidLayoutSubviews
{
    [super viewDidLayoutSubviews];
    
    [metalView setTranslatesAutoresizingMaskIntoConstraints:NO];
    NSDictionary *views = NSDictionaryOfVariableBindings(metalView);
    [self.view addConstraints: [NSLayoutConstraint constraintsWithVisualFormat:@"H:|[metalView]|" options:0 metrics:nil views:views]];
    [self.view addConstraints: [NSLayoutConstraint constraintsWithVisualFormat:@"V:|[metalView]|" options:0 metrics:nil views:views]];
    metalView.contentScaleFactor = self.view.window.contentScaleFactor;
}

- (void)mtkView:(MTKView *)view drawableSizeWillChange:(CGSize)size {
    self.metalView.contentScaleFactor = self.view.window.contentScaleFactor;
    
    CGFloat screenScale = [[UIScreen mainScreen] scale];
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    dlUpdateSize(screenScale * screenBounds.size.width, screenScale * screenBounds.size.height);
}

- (void)drawInMTKView:(MTKView *)view{
    //id<CAMetalDrawable> drawable = view.currentDrawable;
    //MTLRenderPassDescriptor* descriptor = view.currentRenderPassDescriptor;
    
    //mnvgClearWithColor(ctx, nvgRGBA(255,128,0,255));
    
    dlDrawFrame();
    return;
    
//    if(drawable && descriptor)
//    {
//        id<MTLCommandBuffer> commandBuffer = [self.commandQueue commandBuffer];
//        id<MTLRenderCommandEncoder> commandEncoder = [commandBuffer renderCommandEncoderWithDescriptor:descriptor];
//        
//        //dlDrawFrame();
//        
//        [commandEncoder endEncoding];
//        [commandBuffer presentDrawable:drawable];
//        [commandBuffer commit];
//    }
}

@end
