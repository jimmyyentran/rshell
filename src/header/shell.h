#ifndef _SHELL_
#define _SHELL_

#include <limits.h>
#include "runner.h"

enum ShellType {normal, test, boolTest};

class Shell{
    private:
        ShellType shellType;
        char hostname[HOST_NAME_MAX];
        char username[LOGIN_NAME_MAX];

        void getLoginInfo();
        void printPrompt();
    public:
        static const int MAX_INPUT2 = 100;
        Shell();
        Shell(const char *);
        void startShell();
};

#endif
