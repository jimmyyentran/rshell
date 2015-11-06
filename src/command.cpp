#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <sys/wait.h>
#include <cstring>
#include <cstdlib>
#include "header/command.h"

Command::Command(char ** cmd){
    args = cmd;
    std::cout << cmd << std::endl;
    std::cout << args << std::endl;
}

bool Command::run(bool b) {
    // bool b should not be false
    if(!b){
        std::cerr << "This function shouldn't receive a false boolean!";
        return false;
    }

    // if enter exit
    if(strcmp(args[0], "exit") == 0){
        exit(0);
    }

    pid_t child_pid = fork();
    int status;
    if(child_pid >= 0){
        if(child_pid == 0){ // child process
            if (-1 == execvp( *args, args)){
                perror("Can't execute");
                exit(1);
            }
        }else{ // parent process
            wait(&status);
            if (WIFEXITED(status)){
                if(!WEXITSTATUS(status)){
                    return true;
                }
            }
            return false;
        }
    }else{
        perror("Forking error");
        return false;
    }
    return false;
}

void Command::print(){
    char ** it = args;
    while (*it != NULL){
        std::cout << *it++ << std::endl;
    }
}

Command::~Command(){
    std::cout << "Command Destructor Called " << std::endl;
    unsigned i = 0;
    for (; i < 4; i++){
        std::cout << i << std::endl;
        if(args[i] == NULL){
            std::cout << "NULL" << std::endl;
        }else {
            std::cout << args[i] << std::endl;
        }
    }
    // std::cout << &(args[ 0 ]) << std::endl;
    // std::cout << &(args[ 0 ][0]) << std::endl;
    // delete args[1];
    // delete args[0];
    // delete args;
    // char ** it = args;
    // while (*it != NULL){
        // std::cout << *it << std::endl;
        // // delete args[i];
    // }
    // delete args[30];
}

