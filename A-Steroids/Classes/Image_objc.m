//
//  Image_objc.m
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 18.06.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#import "Image_objc.h"
#import "FileUtils_objc.h"

@implementation Image_objc  

+(ImageInfo *)getImageData:(const char *)filePath
{
    NSString *fullPath = [NSString stringWithUTF8String:filePath];
    
    CGImageRef spriteImage = [UIImage imageNamed:fullPath].CGImage;
    
    if (!spriteImage) {
        NSLog(@"Error loading image %s", filePath);
        exit(1);
    }
    
    size_t width = CGImageGetWidth(spriteImage);
    size_t height = CGImageGetHeight(spriteImage);
    
    GLubyte * spriteData = (GLubyte *) calloc(width*height*4, sizeof(GLubyte));
    
    CGContextRef spriteContext = CGBitmapContextCreate(spriteData, width, height, 8, width*4,
                                                       CGImageGetColorSpace(spriteImage), kCGImageAlphaPremultipliedLast);
    
    CGContextDrawImage(spriteContext, CGRectMake(0, 0, width, height), spriteImage);
    CGContextRelease(spriteContext);
    
    ImageInfo *info = malloc(sizeof(ImageInfo));
    info->size.width = width;
    info->size.height = height;
    info->data = spriteData;
    
    return info;
}

@end
