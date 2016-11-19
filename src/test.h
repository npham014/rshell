#ifndef __TEST_H__
#define __TEST_H__

#include "command.h"

class Test : public command {
    public:
    struct stat buf;
    string flag;
    char* path;
    int status;
    bool ready;
    
    Test(string, string);
    int runCommand();
};
#endif