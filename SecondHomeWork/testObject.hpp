//
//  testObject.hpp
//  abbyyCompilatorsAndLanguages
//
//  Created by Clumpy Tuna on 25.04.2018.
//  Copyright © 2018 Clumpy Tuna. All rights reserved.
//

#ifndef testObject_hpp
#define testObject_hpp

#include <stdio.h>
#include "unwindingObj.hpp"

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
  int val_;
};


#endif /* testObject_hpp */
