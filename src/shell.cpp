#include <iostream>
#include <unistd.h>
#include <cstdio>
#include "header/shell.h"
#include "header/parser.h"
#include "header/runner.h"
#include "header/command.h"
#include <sys/wait.h>

Shell::Shell(){
    getLoginInfo();
    // startShell();
}

void Shell::getLoginInfo(){
    if (-1 == gethostname(hostname, HOST_NAME_MAX)){
        perror("Get host failed");
    }
    if (-1 == getlogin_r(username, LOGIN_NAME_MAX)){
        perror("Get login failed");
    }
}

void Shell::printPrompt(){
    std::cout << username << "@" << hostname << "$ ";
}

void Shell::startShell(){
    while(1){
        // char *input =  new char[MAX_INPUT2];
        char input[MAX_INPUT2];
        printPrompt();
        std::cin.getline(input, MAX_INPUT2);

        // if empty input
        if(*input == '\0'){
            continue;
        }

        Parser* parser = new Parser(input);
        parser->runRunners();
        // parser->test();
    }
}

void Shell::runShell(std::queue<Runner*> runners){
    std::cout << "pointer: " << &(runners.front()) << std::endl;
    runners.front()->test();
    // runners.front()->run();
}

void Shell::test(){
}



