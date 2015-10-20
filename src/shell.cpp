#ifndef _SHELL_
#define _SHELL_

#include <iostream>
#include <unistd.h>
#include <limits.h>
#include <cstdio>
#include "parser.cpp"

class Shell{
    private:
        char hostname[HOST_NAME_MAX];
        char username[LOGIN_NAME_MAX];
        const int maxInput = 100;

        void getLoginInfo(){
            if (-1 == gethostname(hostname, HOST_NAME_MAX)){
                perror("Get host failed");
            }
            if (-1 == getlogin_r(username, LOGIN_NAME_MAX)){
                perror("Get login failed");
            }
        }

        void printPrompt(){
            std::cout << username << "@" << hostname << "$ ";
        }

    public:
        Shell(){
            std::cout << "Shell initiated" << std::endl;
            getLoginInfo();
            // startShell();
        }

        void startShell(){
            char input[MAX_INPUT];
            std::cout << "Start Shell" << std::endl;
            printPrompt();
            std::cin.getline(input, MAX_INPUT);
            Parser(input);

        }


};

#endif
