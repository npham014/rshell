#include "test.h"

Test::Test(string name, string f){
    
    this->path = new char[name.size()];
    for (unsigned i = 0; i < name.size(); ++i){
        path[i] = name.at(i);
    }
    path[name.size()] = '\0';
    
    this->flag = f;
    this->status = 1;
    this->ready = true;
    
}

int Test::runCommand(){
    //cout << "test" << endl;
    this->ready = false;
    int temp = stat(path , &buf);
    
    if (temp < 0){                              //failed to create struct
        this->status = 0;
        cout << "(False)" << endl;
        return this->status;
    }
    if (this->flag == "-e"){
        cout << "(True)" << endl;
        return this->status;
    }
    if (this->flag == "-f"){
        if (S_ISREG(buf.st_mode) == 0){
            cout << "(True)" << endl;
            return this->status;
        }
        this->status = 0;
        cout << "(False)" << endl;
        return this->status;
    }
    if (this->flag == "-d"){
        if (S_ISDIR(buf.st_mode) == 0){
            cout << "(True)" << endl;
            return this->status;
        }
        this->status = 0;
        cout << "(False)" << endl;
        return this->status;
    }
    
    return this->status;
}