#include <stdio.h>
#include <iostream>
#include <map>
#include <string>


#define VIRTUAL_CLASS( baseClassName )                                         \
class baseClassName {                                                          \
public:                                                                        \
  baseClassName();                                                             \


#define DECLARATION_BASE_CLASS_END                                             \
public:                                                                        \
  std::map<std::string, void(*)()> vtable;                                     \
};                                                                             \

#define DECLARE_METHOD( className, methodName )                                \
void className ## methodName() {                                               \
  std::cout << #className "::" << #methodName << std::endl;                    \
}                                                                              \

#define ADD_METHOD( className, methodName )                                    \
vtable[#methodName] = className ## methodName;                                 \

#define CONSTRUCTOR_BEGIN( className )                                         \
className::className()                                                         \
{                                                                              \


#define CONSTRUCTOR_END                                                        \
};



#define VIRTUAL_CLASS_DERIVED( derivedClassName, baseClassName )               \
class derivedClassName : public baseClassName {                                \
public:                                                                        \
  derivedClassName();

#define DECLARATION_DERIVED_CLASS_END                                          \
};


#define VIRTUAL_CALL(classToCall, methodToCall)                                \
classToCall->vtable[#methodToCall]();



// Объявим базовый класс
VIRTUAL_CLASS( Base )
int a = 0;
DECLARATION_BASE_CLASS_END

// Объявим в нем два метода
DECLARE_METHOD( Base, doSomething )
DECLARE_METHOD( Base, doNothing )


// Реализация преполагает подобную конструкцию
// для поддержки виртуальных вызовов
CONSTRUCTOR_BEGIN( Base )

ADD_METHOD( Base, doSomething )
ADD_METHOD( Base, doNothing )

CONSTRUCTOR_END



// Объявим класс наследник
VIRTUAL_CLASS_DERIVED( Derived, Base )
int a = 1;
DECLARATION_DERIVED_CLASS_END

// Обратим внимание, что метод doNothing не задекларирован в наследнике
DECLARE_METHOD( Derived, doSomething )

CONSTRUCTOR_BEGIN( Derived )

ADD_METHOD( Derived, doSomething )

CONSTRUCTOR_END

int main() {

  Base* a = new Base;
  
  Derived* b = new Derived;
  
  Base* reallyDerived = reinterpret_cast<Base*>( b );
  // Согласно требованиям задания продемонстрируем три варианта поведения
  // 1) Метод, определённый в базовом “классе”,
  //    но не в классе-наследнике должен быть найден и вызван для наследника.
  std::cout << "First case:" << std::endl;
  VIRTUAL_CALL(b, doNothing)
  
  // 2) Метод, определённый в базовом “классе”, но переопределенный в наследнике,
  //    должен учитывать тип объекта, у которого метод вызван.
  VIRTUAL_CALL( reallyDerived, doSomething )
  
  // 3) Метод, не определённый для данного класса, может компилироваться,
  //    но бросать исключение. Или не компилироваться - на Ваше усмотрение.
  
  return 0;
}
