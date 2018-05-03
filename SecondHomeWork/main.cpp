// Дефайны для работы с исключениями,
// пример использования ниже
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

// Функция перевешивает указатель на следующий Scope
int popScope() {
  scopeBuffer *tmp = currentScope;
  currentScope = tmp->previousScope;
  return 0;
}

// Функция развертки стека. У всех объектов в scope, наследованных от unwindingObject,
// вызывается деструктор.
int unwindingStack(int status, bool shouldPopScope) {
  scopeBuffer *scope = currentScope;
  unwindingObject *object = currentScope->objects;
  
  while (object != nullptr) {
    unwindingObject *tmp = object;
    object = object->previousObject;
    tmp->~unwindingObject();
  }
  
  if (shouldPopScope) {
    popScope();
  }
  
  longjmp (scope->buffer, status);
  
  return 0;
}


////////////////////////////////////////////////////////////////////////////////
// Пример класса, который будет уничтожен при раскрутке стека
class testObject : public unwindingObject {
public:
  testObject() : val_() {
    printf ("A::A(%d)\n",val_);
  }
  
  testObject(int i) : val_(i) {
    printf ("A::A(%d)\n",val_);
  }
  
  virtual ~testObject() {
    printf ("A::~A(%d)\n",val_);
  }

private:
  int val_;
};
////////////////////////////////////////////////////////////////////////////////

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


