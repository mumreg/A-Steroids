//
//  FileUtils_objc.m
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 25.06.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#import "FileUtils_objc.h"

@implementation FileUtils_objc

+(const char *)getFullPathFor:(NSString *)fileName
{
    NSString* fullpath = [[NSBundle mainBundle] pathForResource:fileName
                                                         ofType:nil];
    
    NSLog(@"%@", fullpath);
    
    if (fullpath != nil) {
        return [fullpath UTF8String];
    }
    
    return nil;
}

@end
