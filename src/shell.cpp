#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include "header/shell.h"
#include "header/parser.h"
#include <sys/wait.h>

Shell::Shell() : shellType(normal){
    getLoginInfo();
}

Shell::Shell(const char * type){
    getLoginInfo();
    if(strcmp(type, "TEST") == 0){
        shellType = test;
    } else if (strcmp(type, "BOOLTEST") == 0){
        shellType = boolTest;
    } else {
        shellType = normal;
    }
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
        char input[MAX_INPUT2];
        printPrompt();
        std::cin.getline(input, MAX_INPUT2);

        if(shellType > normal){
            std::cout << input << std::endl;
        }

        // if empty input
        if(*input == '\0'){
            continue;
        }

        Parser parser = Parser(input);

        try {
            parser.parserInit();
        } catch (const std::exception& e){
            printf("%s\n", e.what());
        }

        if(shellType == boolTest){
            parser.test();
        } else {
            parser.runRunners();
        }

        // Parser* parser = new Parser(input);
        // try {
        // if(shellType == boolTest){
        // parser->test();
        // } else {
        // parser->runRunners();
        // }
        // delete parser;
        // } catch (const std::exception& e){
        // // delete parser;
        // }

    }
}
