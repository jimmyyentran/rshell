#ifndef _CONNECTOR_
#define _CONNECTOR_

#include <cstdio>
#include <iostream>
#include "runner.h"

// Abstract class
class Connector : public Runner {
    private:
        char * key;
        bool ifReceiveTrue;
        bool ifReceiveFalse;
    public:
        Connector(){};
        Connector(char *);
        Connector(char *, bool, bool);
        void setKey(char*);
        bool run(bool);
        void print();
        virtual ~Connector() = 0;
};

#endif
