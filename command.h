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
    int status;
    int getStatus();           //returns the status of the command
    command() {status = 1;};
    command(vector<string> commInputs);
    void runCommand();
    
};

#endif