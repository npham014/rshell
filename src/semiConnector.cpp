#include "semiConnector.h"



void semiConnector::run(command* left, command* right){
    if (left->ready) {              //checks if the first function was run yet
        left->runCommand();                 
    }
    right->runCommand();            //runs the second regardless

}