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
        void Run();
        void Parse(string commandLine);
        void createCommands();
        void runAllCommands();
        void clearCommands();
};

#endif