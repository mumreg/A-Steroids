//
//  Image_objc.h
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 18.06.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "datatypes.h"

@interface Image_objc : NSObject

+(ImageInfo *)getImageData:(const char *)filePath;

@end
