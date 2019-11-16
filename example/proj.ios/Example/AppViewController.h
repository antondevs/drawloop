//
//  AppViewController.h
//  Example
//
//  Created by Developer on 26.10.2019.
//  Copyright © 2019 Developer. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Metal/Metal.h>
#import <MetalKit/MetalKit.h>

@interface AppViewController : UIViewController<MTKViewDelegate>

@property (strong, nonatomic) MTKView *metalView;
@property (strong, nonatomic) id<MTLCommandQueue> commandQueue;

@end
