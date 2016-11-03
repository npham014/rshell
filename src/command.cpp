#include "command.h"

command::command(vector<string> commInputs) {           //Initialize command status and the actual commands.
     status = 1;    
     ready = true;
     commands = commInputs;
}

int command::runCommand(){
    if(commands.at(0) == "exit") {
        rshellExit();
        return status;
    }
    unsigned int temp = commands.size() + 1;             
    char** commsArr = new char*[temp];                  //Change the vector of strings into an array of cstrings.
    for(unsigned int i = 0; i < commands.size(); ++i) {
        commsArr[i] = (char*)commands.at(i).c_str();
    }
    commsArr[commands.size()] = NULL;
    
    pid_t pid = fork();// Fork the current process
    if(pid == -1) {//Make sure fork worked
        this->status = 0;
        perror("fork failed");
    }
    
    if(pid == 0) {                                      //Child function
        if(execvp(commsArr[0], commsArr) == -1) {       //Try to execute the command
            this->status = 0;
            perror("execute failed");
        }
    }
    
    if(pid > 0) {                                       //halt the parent function
        if(wait(0) == -1) {
            this->status = 0;
            perror("wait failed");
        }
            
    }
    this->ready = false;
    delete[] commsArr;
    return status;
}

int command::getStatus(){
    return this->status;                                //returns the status
}

void command::rshellExit() {
    status = -5;
    ready = false;
}