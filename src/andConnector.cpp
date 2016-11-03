#include "andConnector.h"



void andConnector::run(command* left, command* right) {
    
        if (left->ready) {
            left->runCommand();         //checks if the function has already been run
        }
        
        if (left->getStatus()) {
            right->runCommand();        //checks to make sure the first function ran successfully to run
        }
        else {
            right->status = 0;          //if the first did not run, this will not run and the status will be set to 0
            right->ready = false;
        }
    
    
    
}