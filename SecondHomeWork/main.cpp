
#define                                                \
TRY {                                                  \
  scopeBuffer __scope;                                 \
  const int __exc = (const int)setjmp(__scope.buffer); \
  if (__exc == 0) {

#define CATCH                                          \
  } else {

#define FINILIZE                                       \
  }                                                    \
}

#define THROW_IN_BLOCK(exc)                            \
unwindingStack(exc, true);


#define RETHROW_IN_BLOCK                               \
unwindingStack(__exc, false);


#include <csetjmp>
#include <iostream>
#include <assert.h>

#include "unwindingObj.hpp"
#include "scopeBuffer.hpp"
#include "global.h"
#include "testObject.hpp"

int pop_slice() {
  scopeBuffer *tmp = currentScope;
  currentScope = tmp->previousScope;
  return 0;
}

int unwindingStack(int status, bool popstate) {
  scopeBuffer *scope = currentScope;
  unwindingObject *object = currentScope->objects;
  
  while (object != nullptr) {
    unwindingObject *tmp = object;
    object = object->previousObject;
    tmp->~unwindingObject();
  }
  
  if (popstate) {
    pop_slice();
  }
  
  longjmp (scope->buffer, status);
  
  return 0;
}


int main() {
  testObject a(1);
  TRY {
    testObject b(2);
    THROW_IN_BLOCK(1);
    std::cerr << "notreached\n";
  }
  CATCH {
    std::cerr << __exc << std::endl;
  }
  FINILIZE;
  
  return 0;
}


