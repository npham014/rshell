#ifndef __COMMAND__
#define __COMMAND__
#include <vector>
#include<string>
#include<iostream>
#include <cstdio>
#include <stdlib.h>
#include <cstdlib>
#include <unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include <string>
using namespace std;

class command {
    
    public:
    vector<string> commands;
    int status;                                 //check if it runs correctly
    bool ready;                                 //check if it has run yet or ready to be ran
    
    int getStatus();                            //returns the status of the command
    command() {status = 1; ready = true;};
    command(vector<string> commInputs);
    int runCommand();
    void rshellExit();
};

#endif