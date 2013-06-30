//
//  ASet.cpp
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 30.06.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#include "ASet.h"

using namespace std;

void ASet::addObject(APoint *object)
{
    _set.insert(object);
}

int ASet::getSize()
{
    return _set.size();
}

APoint *ASet::getObjectAtIndex(unsigned int index)
{
    if (index > _set.size()) {
        return NULL;
    }
    
    set<APoint *>::iterator it = _set.begin();
    for (int i = 0; i < index; i++, ++it);
    
    return (*it);
}

void ASet::removeAllObjects()
{
    for (int i = 0; i < _set.size(); i++) {
        APoint *point = getObjectAtIndex(i);
        delete point;
    }
    _set.erase(_set.begin(), _set.end());
}
