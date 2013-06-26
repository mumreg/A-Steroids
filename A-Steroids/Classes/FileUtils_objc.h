//
//  FileUtils_objc.h
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 25.06.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface FileUtils_objc : NSObject

+(const char *)getFullPathFor:(NSString *)fileName;

@end
