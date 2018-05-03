//
//  unwindingObj.cpp
//  abbyyCompilatorsAndLanguages
//
//  Created by Clumpy Tuna on 25.04.2018.
//  Copyright © 2018 Clumpy Tuna. All rights reserved.
//

#include "unwindingObj.hpp"
#include "scopeBuffer.hpp"

extern scopeBuffer *currentScope;

unwindingObject::unwindingObject() {
  if (currentScope != nullptr) {
    previousObject = currentScope->objects;
    currentScope->objects = this;
  }
}

unwindingObject::~unwindingObject() {
  deleteFromScope();
}

void unwindingObject::deleteFromScope() {
  if (currentScope != nullptr) {
    currentScope->objects = previousObject;
  }
}

