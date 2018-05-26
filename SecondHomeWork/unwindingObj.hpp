//
//  unwindingObj.hpp
//  abbyyCompilatorsAndLanguages
//
//  Created by Clumpy Tuna on 25.04.2018.
//  Copyright © 2018 Clumpy Tuna. All rights reserved.
//

#ifndef unwindingObj_hpp
#define unwindingObj_hpp

#include <stdio.h>

// Класс от которого необходимо наследоваться для корректной работы раскрутки
// стека. Объекты будут провязаны в список, а затем один за другим удалены.

class unwindingObject {
public:
  unwindingObject();
  virtual ~unwindingObject();
  void deleteFromScope();
  unwindingObject *previousObject;
};


#endif /* unwindingObj_hpp */

