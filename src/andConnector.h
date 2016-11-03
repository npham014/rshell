#ifndef __ANDCONNECTOR__
#define __ANDCONNECTOR__

#include "connector.h"
#include "command.h"

class andConnector :public connector {
    
    public:

    andConnector(){ };
    void run(command* left, command* right);
};

#endif