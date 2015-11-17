#ifndef _COMMAND_
#define _COMMAND_

#include "runner.h"

class Command : public Runner{
    protected:
        char * args[30];
    public:
        Command(char ** cmd);
        ~Command();
        bool run(bool);
        void print();
        bool runTest();
};

#endif
