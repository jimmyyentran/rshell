#ifndef _COMMAND_
#define _COMMAND_

#include "runner.h"

class Command : public Runner{
    private:
        // char **args;
        // char args[30][30];
        char * args[30];
    public:
        Command(char ** cmd);
        ~Command();
        bool run(bool);
        void print();
};

#endif
