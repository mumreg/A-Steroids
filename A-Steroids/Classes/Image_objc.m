//
//  Image_objc.m
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 18.06.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#import "Image_objc.h"

@implementation Image_objc  

+(ImageInfo *)getImageData:(const char *)filePath
{
    NSString *fullPath = [NSString stringWithUTF8String:filePath];
    UIImage *png = [[UIImage alloc] initWithContentsOfFile:fullPath];
    
    
    
    [png release];
}

@end
