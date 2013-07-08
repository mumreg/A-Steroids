//
//  AppDelegate.h
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 01.07.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GLViewController.h"

@interface AppDelegate : UIResponder <UIApplicationDelegate>
{
    GLViewController *_glViewController;
}
@property (strong, nonatomic) UIWindow *window;
@property (nonatomic, retain) IBOutlet GLViewController *glViewController;

@end
