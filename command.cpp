#include "command.h"

command::command(vector<string> commInputs) {//Initialize command status and the actual commands.
     status = 1;
     commands = commInputs;
}

void command::runCommand(){
                                    
    char* commsArr[commands.size() + 1];//Change the vector of strings into an array of cstrings.
    for(int i = 0; i < commands.size(); ++i) {
        commsArr[i] = (char*)commands.at(i).c_str();
    }
    commsArr[commands.size()] = NULL;
    
    pid_t pid = fork();// Fork the current process
    if(pid == -1) {//Make sure fork worked
        this->status = -1;
        perror("fork failed");
    }
    
    if(pid == 0) { //Child function
        if(execvp(commsArr[0], commsArr) == -1) {//Try to execute the command
            this->status = -1;
            perror("execute failed");
        }
    }
    
    if(pid > 0) { //halt the parent function
        if(wait(0) == -1) {
            this->status = -1;
            perror("wait failed");
        }
        //Can do something in parent here if we need
    }
}

int command::getStatus(){
    return this->status;            //returns the status
}