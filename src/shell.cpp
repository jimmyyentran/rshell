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
    while(1){
        char input[MAX_INPUT2];
        printPrompt();
        std::cin.getline(input, MAX_INPUT2);

        // if empty input
        if(*input == '\0'){
            continue;
        }

        std::cout << input << std::endl;

        Parser parser = Parser(input);
        parser.runRunners();
    }
}

void Shell::runShell(std::queue<Runner*> runners){
    std::cout << "pointer: " << &(runners.front()) << std::endl;
    runners.front()->test();
    // runners.front()->run();
}

void Shell::test(){
    char *array[10];
    array[0] = (char*)"ls";
    array[1] = (char*)"-al";
    array[2] = NULL;
    Runner *test =  new Command(array);
    test->run();
}



