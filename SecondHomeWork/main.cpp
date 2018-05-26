//
//  main.cpp
//  Exception
//
//  Created by Clumpy Tuna on 26.04.2018.
//  Copyright © 2018 Clumpy Tuna. All rights reserved.
//

bool caught = true;

// Разные типы исключений
#define BAD_ALLOC_EXCEPTION 1
#define BAD_ACCESS_EXCEPTION 2
#define BAD_CAST_EXCEPTION 3
#define BAD_TYPEID 4
#define BAD_FUNCTION_CALL 5
#define BAD_WEAK_PTR 6
#define LOGIC_ERROR_EXCEPTION 7
#define RUNTIME_EXCEPTION 8
////////////////////////////////////////////////////////


// Дефайны для работы с исключениями,
// пример использования ниже
#define                                                \
TRY {                                                  \
  scopeBuffer __scope;                                 \
  const int __exc = (const int)setjmp(__scope.buffer); \
                                                       \
if (__exc == 0) {

#define CATCH(exceptionType)                           \
} else if (__exc == exceptionType) {                   \
  caught = true;

#define TRY_END                                        \
  }                                                    \
  if (!caught) exit(-1);                               \
}

#define THROW_IN_BLOCK(exc)                            \
unwindingStack(exc, true);


#define RETHROW_IN_BLOCK                               \
unwindingStack(__exc, false);


#include <csetjmp>
#include <iostream>

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
void unwindingStack(int status, bool shouldPopScope) {
  caught = false;
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
  
  //jumps to specified location
  longjmp (scope->buffer, status);
}


////////////////////////////////////////////////////////////////////////////////
// Пример класса, который будет уничтожен при раскрутке стека
class testObject : public unwindingObject {
public:
  testObject() : val_(0) {
    printf ("A::A(%d)\n",val_);
 }
 
  testObject(int i) : val_(i) {
    printf ("A::A(%d)\n",val_);
 }
 
 virtual ~testObject() {
   printf ("A::~A(%d)\n",val_);
 }
 
private:
 int val_ = 0;
};

////////////////////////////////////////////////////////////////////////////////


int main() {
  // Кидаем исключение определенного типа
  // и ловим исключение того же типа. И все работает!
  TRY {
    testObject b(1);
    THROW_IN_BLOCK(BAD_ALLOC_EXCEPTION);
  }
  CATCH(BAD_ALLOC_EXCEPTION) {
    std::cout << "BAD_ALLOC_EXCEPTION пойман" << std::endl;
  }
  TRY_END;
  
  // Кидаем исключение, а ловим исключение другого -  как итог
  // завершаем работу c ненулыевым кодом возврата .
  TRY {
    THROW_IN_BLOCK(BAD_ALLOC_EXCEPTION);
  }
  CATCH(RUNTIME_EXCEPTION) {
    std::cout << "RUN_TIME_EXCEPTION пойман" << std::endl;
  }
  TRY_END
  
  return 0;
}



