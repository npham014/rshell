#include "andConnector.h"



void andConnector::run(command* left, command* right) {
    if (left) {
        left->runCommand();                         //runs first command, checks if it finished before running second
        if (left->getStatus()){
            right->runCommand();
        }
    
            right->status = 0;
    }
}