//
//  scopeBuffer.cpp
//  abbyyCompilatorsAndLanguages
//
//  Created by Clumpy Tuna on 25.04.2018.
//  Copyright © 2018 Clumpy Tuna. All rights reserved.
//

#include "scopeBuffer.hpp"

extern scopeBuffer *currentScope;

scopeBuffer::scopeBuffer() {
  objects = nullptr;
  previousScope = currentScope;
  currentScope = this;
}

scopeBuffer::~scopeBuffer() {
  currentScope = previousScope;
}
