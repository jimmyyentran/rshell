#include <iostream>
#include <unistd.h>
#include <limits.h>
#include <cstdio>
#include <pwd.h>
#include "header/shell.h"
#include "header/parser.h"

Shell::Shell(){
    std::cout << "Shell initiated" << std::endl;
    getLoginInfo();
    // startShell();
}

void Shell::getLoginInfo(){
    if (-1 == gethostname(hostname, HOST_NAME_MAX)){
        perror("Get host failed");
    }
    // username = getlogin();
    // perror ("getlogin() error");
    // if (username == NULL)
    if (-1 == getlogin_r(username, LOGIN_NAME_MAX)){
        perror("Get login failed");
    }
}

void Shell::printPrompt(){
    std::cout << username << "@" << hostname << "$ ";
}

void Shell::startShell(){
    char input[MAX_INPUT2];
    std::cout << "Start Shell!" << std::endl;
    printPrompt();
    std::cin.getline(input, MAX_INPUT2);
    Parser parser = Parser(input);
    parser.test();
    // std::cout << "Test" << std::endl;
}
