#ifndef __SEMICONNECTOR__
#define __SEMICONNECTOR__

#include "connector.h"
#include "command.h"
class semiConnector :public connector {
    
    public:
    semiConnector() {};
    void run(command* left, command* right);        
};

#endif