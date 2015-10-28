#ifndef _SHELL_
#define _SHELL_

#include <limits.h>
#include "runner.h"

class Shell{
    private:
        char hostname[HOST_NAME_MAX];
        char username[LOGIN_NAME_MAX];

        void getLoginInfo();
        void printPrompt();
    public:
        static const int MAX_INPUT2 = 100;

        Shell();
        void startShell();
};

#endif
