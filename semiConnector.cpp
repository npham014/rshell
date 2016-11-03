#include "semiConnector.h"



void semiConnector::run(command* left, command* right){

    left->runCommand();                 //runs both commands regardless of status
    right->runCommand();

}