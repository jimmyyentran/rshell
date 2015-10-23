#ifndef _COMMAND_
#define _COMMAND_

#include "runner.h"

class Command : public Runner{
    private:
        char **args;
    public:
        Command(char ** cmd);
        bool run();
        void test();
};

#endif
