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

class unwindingObject {
public:
  unwindingObject();
  virtual ~unwindingObject();
  void deleteFromScope();
  
public:
  unwindingObject *previousObject;
};


#endif /* unwindingObj_hpp */
