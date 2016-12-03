#include "cdCommand.h"

cdCommand::cdCommand(vector<string> commInputs){
    status = 1;
    ready = true;
    commands = commInputs;
}

int cdCommand::runCommand(){
    
    if (commands.size() < 1 || commands.size() > 2){
        this->status = 0;
        this->ready = false;
        return status;
    }
    
    if (commands.size() == 1){ //If command is just "cd" -> goes to the home directory      (CASE: 1)
        const char* homecstring = "HOME";
        if (chdir(homecstring)){
            const char* temp = getenv("PWD");
            const char* hum = getenv("HOME");
            if (setenv("PWD", hum, 1)){
                this->status = 0;
                this->ready = false;
                return status;
            }
            else if (setenv("OLDPWD", temp, 1)){
                this->status = 0;
                this->ready = false;
                return status;
            }
            else{
                this->ready = 0;
                return status;
            }
        } 
    } 
    char* path = new char[commands.at(1).size()];
    
    for (unsigned i = 0; i < commands.at(1).size(); ++i){
        path[i] = commands.at(1).at(i);
    }
    
    if (commands.at(1) == "-"){         //visit previous directory (CASE: 2)
        path = getenv("OLDPWD");
        const char* path2 = getenv("PWD");
        if (chdir(path)){               //check if it changes directory (fail)
            this->status = 0;
            this->ready = false;
            return this->status;
        }
        
        
        
        if (setenv("PWD", path, 1)){      //if you cannot change the current env pointer to the previous (fail)
            this->status = 0;
            this->ready = false;
            return status;
        }
        else if (setenv("OLDPWD", path2, 1)){    //if you cannot change the OLDPWD to the new previous (fail)
            this->status = 0;
            this->ready = false;
            return status;
        }
        else{                                   //return if passed
            this->ready = false;
            return this->status;
        }
    }
    else{                       //input path name from user (CASE: 3)
        const char* tempp = getenv("PWD");
        if (chdir(path)){
            this->status = 0;
            this->ready = false;
            return this->status;
        }
        else if (setenv("PWD", path, 1)){
            this->status = 0;
            this->ready = false;
            return this->status;
        }
        else if (setenv("OLDPWD", tempp, 1)){
            this->status = 0;
            this->ready = false;
            return this->status;
        }
        else{
            this->ready = false;
            return this->status;
        }
    }
    return this->status;
}
int cdCommand::getStatus(){
    return this->status;
}
void cdCommand::rshellExit(){
    this->status = -5;
    this->ready = false;
}