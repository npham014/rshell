#ifndef __CONNECTOR__
#define __CONNECTOR__

#include "command.h"

class connector {
    
  public:
    
    virtual void run(command*, command*) = 0;         //abstract base class for connectors
};

#endif