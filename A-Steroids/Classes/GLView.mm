//
//  GLView.m
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 20.05.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#import "GLView.h"
#include "ShadersCache.h"

#include "datatypes.h"
#include "TouchDispatcher.h"

@implementation GLView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self setupLayer];
        [self setupContext];
        [self setupDepthBuffer];
        [self setupRenderBuffer];
        [self setupFrameBuffer];
        [self setupDisplayLink];
        
        sprite = new Sprite("item_powerup_fish.png");
        sprite->setTouchEnabled(true);
        sprite->addToTouchDispatcher();
    }
    return self;
}

+(Class)layerClass {
    return [CAEAGLLayer class];
}

-(void)setupLayer
{
    _glLayer = (CAEAGLLayer*)self.layer;
    _glLayer.opaque = YES;
}

-(void)setupContext
{
    EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
    _context = [[EAGLContext alloc] initWithAPI:api];
    if (!_context) {
        NSLog(@"Failed to initialize OpenGLES 2.0 context");
        exit(1);
    }
    
    if (![EAGLContext setCurrentContext:_context]) {
        NSLog(@"Failed to set current OpenGL context");
        exit(1);
    }
}

-(void)setupRenderBuffer
{
    glGenRenderbuffers(1, &_colorRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderBuffer);
    [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:_glLayer];
}

- (void)setupDepthBuffer {
    glGenRenderbuffers(1, &_depthRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _depthRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, self.frame.size.width, self.frame.size.height);
}

-(void)setupFrameBuffer
{
    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _colorRenderBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthRenderBuffer);
}

-(void)setupDisplayLink {
    CADisplayLink* displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(render:)];
    [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}

-(void)render:(CADisplayLink*)displayLink
{
    glClearColor(0, 0, 0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    sprite->render();
    [_context presentRenderbuffer:GL_RENDERBUFFER];
}

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    int ids[MAX_TOUCHES];
    float xs[MAX_TOUCHES];
    float ys[MAX_TOUCHES];
    
    int i = 0;
    
    for (UITouch *touch in touches) {
        CGPoint p = [touch locationInView:self];
        ids[i] = (int)touch;
        xs[i] = p.x * self.contentScaleFactor;
        ys[i] = p.y * self.contentScaleFactor;
        
        i++;
    }

    TouchDispatcher::sharedInstance()->touchesBegan(i, ids, xs, ys);
}

-(void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    int ids[MAX_TOUCHES];
    float xs[MAX_TOUCHES];
    float ys[MAX_TOUCHES];
    
    int i = 0;
    
    for (UITouch *touch in touches) {
        CGPoint p = [touch locationInView:self];
        ids[i] = (int)touch;
        xs[i] = p.x * self.contentScaleFactor;
        ys[i] = p.y * self.contentScaleFactor;
        
        i++;
    }
    
    TouchDispatcher::sharedInstance()->touchesMoved(i, ids, xs, ys);
}

-(void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
{
    int ids[MAX_TOUCHES];
    float xs[MAX_TOUCHES];
    float ys[MAX_TOUCHES];
    
    int i = 0;
    
    for (UITouch *touch in touches) {
        CGPoint p = [touch locationInView:self];
        ids[i] = (int)touch;
        xs[i] = p.x * self.contentScaleFactor;
        ys[i] = p.y * self.contentScaleFactor;
        
        i++;
    }
    
    TouchDispatcher::sharedInstance()->touchesEnded(i, ids, xs, ys);
}

-(void)dealloc
{
    [_context release];
    _context = nil;
    [super dealloc];
}

@end
