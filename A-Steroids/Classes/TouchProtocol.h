//
//  TouchProtocol.h
//  A-Steroids
//
//  Created by Mikhail Perekhodtsev on 30.06.13.
//  Copyright (c) 2013 Mikhail Perekhodtsev. All rights reserved.
//

#ifndef __A_Steroids__TouchProtocol__
#define __A_Steroids__TouchProtocol__

#include <iostream>
#include "ASet.h"

class TouchProtocol {
public:
    virtual void touchesBegan(ASet *set) = 0;
    virtual void touchesMoved(ASet *set) = 0;
    virtual void touchesEnded(ASet *set) = 0;
};

#endif /* defined(__A_Steroids__TouchProtocol__) */
