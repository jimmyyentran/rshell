#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <sys/wait.h>
#include <cstring>
#include <cstdlib>
#include "header/command.h"

Command::Command(char ** cmd){
    char ** it = args;
    while (*cmd != NULL){
        char *tmp = new char[sizeof(*cmd)];
        strcpy(tmp, *cmd++);
        *it++ = tmp;
    }
    *it = NULL;
    test();
}

bool Command::run() {
    // if enter exit
    if(strcmp(args[0], "exit") == 0){
        exit(0);
    }

    pid_t child_pid = fork();
    if(child_pid >= 0){
        if(child_pid == 0){ // child process
            std::cout << "Child Process " << std::endl;
            if (-1 == execvp( *args, args)){
                perror("Can't execute");
                std::cout << "Child return false" << std::endl;
                return false;
            }
            std::cout << "Child return true" << std::endl;
            return true;
        }else{ // parent process
            std::cout << "Parent Process" << std::endl;
            int status;
            waitpid( child_pid, &status, 0);
            std::cout << "Parent return true" << std::endl;
            return true;
        }
    }else{
        perror("Forking error");
        std::cout << "Run return false" << std::endl;
        return false;
    }
    std::cout << "Run return true" << std::endl;
    return true;
}

void Command::test(){
    std::cout << "Command Args: "<< std:: endl;
    char ** it = args;
    while (*it != NULL){
        std::cout << *it++ << std::endl;
    }
}

Command::~Command(){
    std::cout << "Command Destructor Called" << std::endl;
    while (*args != NULL){
        delete [] *args++;
    }
}

