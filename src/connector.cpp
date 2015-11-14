#include "header/connector.h"

Connector::Connector(char * str){
    key = str;
    ifReceiveTrue = 0;
    ifReceiveFalse = 0;
}

Connector::Connector(char * str, bool a, bool b){
    key = str;
    ifReceiveTrue = a;
    ifReceiveFalse = b;
}

void Connector::setKey(char* str){
    key = str;
}

bool Connector::run(bool b){
    return b ? ifReceiveTrue : ifReceiveFalse;
}

void Connector::print(){
    printf("%s\n", key);
}

Connector::~Connector(){
    // std::cout << "Connector Destructor Called " << std::endl;
}
