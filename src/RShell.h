#ifndef __RSHELL__
#define __RSHELL__

// class parameter;
// class command;
// class connector;
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "command.h"
#include "connector.h"
#include "andConnector.h"
#include "orConnector.h"
#include "semiConnector.h"
#include <cstdlib>
#include <string>
#include <cstring>
#include <unistd.h>
#include <algorithm>
#include <cctype>

using namespace std;

class RShell {
    public:
        vector<string> tokens;
        vector<string> connectorStrings;
        vector<command*> commandList;
        vector<vector<string> > commandChunks;
        vector<string> connectorTokens;
        vector<connector*> connectorList;
        RShell();
        void Run();                             //runs the entire program
        void Parse(string commandLine);         //filters through the commands and connectors
        void createCommands();                  //filters through chunks to seperate commands and arguments
        int runAllCommands();                   //executes the commands and connectors
        void clearCommands();                   //clears all of the allocated memory
};

#endif