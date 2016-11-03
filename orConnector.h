#ifndef __ORCONNECTOR__
#define __ORCONNECTOR__

#include "connector.h"
#include "command.h"
class orConnector :public connector {
    
    public:

    orConnector(){ };
    void run(command* left, command* right);
};

#endif