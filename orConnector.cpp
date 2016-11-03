#include "orConnector.h"



void orConnector::run(command* left, command* right){
    if (left){
        left->runCommand();             //runs first command, only runs the second if the first fails
        if (!left->getStatus()) {
            right->runCommand();
        }
        else {
            right->status = 0;
        }
    }
}