//
//  ASet.h
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 30.06.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#ifndef __A_Steroids__ASet__
#define __A_Steroids__ASet__

#include <iostream>
#include <set>

#include "datatypes.h"

class ASet {
public:
    ASet() {}
    void addObject(APoint *object);
    void removeAllObjects();
    APoint *getObjectAtIndex(unsigned int index);
    
    int getSize();
    
private:
    std::set<APoint *> _set;
};

#endif /* defined(__A_Steroids__ASet__) */
