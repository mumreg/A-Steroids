//
//  TouchDispatcher.h
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 30.06.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#ifndef __A_Steroids__TouchDispatcher__
#define __A_Steroids__TouchDispatcher__

#include <iostream>
#include <vector>

#include "Node.h"

class TouchDispatcher {
public:
    static TouchDispatcher *sharedInstance();
    
    void addObject(Node *object);
    void removeObject(Node *object);
    
//    -(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
//    -(void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
//    -(void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
    
    void touchesBegan(int num, int *ids, float *xs, float *ys);
    void touchesMoved(int num, int *ids, float *xs, float *ys);
    void touchesEnded(int num, int *ids, float *xs, float *ys);
    
private:
    TouchDispatcher() {}
    TouchDispatcher(TouchDispatcher&) {}
    TouchDispatcher& operator=(TouchDispatcher&);
    
    std::vector<Node *> _objects;
};

#endif /* defined(__A_Steroids__TouchDispatcher__) */
