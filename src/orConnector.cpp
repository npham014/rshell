#include "orConnector.h"



void orConnector::run(command* left, command* right) {
    
        if (left->ready) {                  //checks if the first function has been run yet
            left->runCommand(); 
        }                   
        if (!(left->getStatus())) {         //runs only if the first failed to
            right->runCommand();
        }
        else {
            right->status = 0;              //if not, then it is not cleared to run
            right->ready = false;
        }
}
