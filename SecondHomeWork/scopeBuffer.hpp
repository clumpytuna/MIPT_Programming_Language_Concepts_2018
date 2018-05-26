//
//  scopeBuffer.hpp
//  abbyyCompilatorsAndLanguages
//
//  Created by Clumpy Tuna on 25.04.2018.
//  Copyright © 2018 Clumpy Tuna. All rights reserved.
//

#ifndef scopeBuffer_hpp
#define scopeBuffer_hpp

#include <stdio.h>
#include <csetjmp>
#include "unwindingObj.hpp"

class scopeBuffer {
  
public:
  scopeBuffer();
  ~scopeBuffer();
  
public:
  jmp_buf buffer;
  unwindingObject *objects;
  scopeBuffer *previousScope;
  
};
#endif /* scopeBuffer_hpp */

