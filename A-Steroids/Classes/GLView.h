//
//  GLView.h
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 20.05.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#include "Sprite.h"

@interface GLView : UIView
{
    CAEAGLLayer *_glLayer;
    EAGLContext *_context;
    GLuint _colorRenderBuffer;
    GLuint _depthRenderBuffer;
    Sprite *sprite;
}

@end
