#ifndef __CD_H__
#define __CD_H__

#include "command.h"
using namespace std;

class cdCommand : public command {
    
    public:
    vector <string> commands;
    int status;
    bool ready;
    
    cdCommand(vector <string> commInputs);
    int getStatus();
    int runCommand();
    void rshellExit();
    
    
};
#endif