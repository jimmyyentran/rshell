#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <sys/wait.h>
#include <cstring>
#include <cstdlib>
#include "header/command.h"

Command::Command(char ** cmd){
    args = cmd;
}

bool Command::run() {
    // if enter exit
    if(strcmp(args[0], "exit") == 0){
        std::cout << "Exiting!" << std::endl;
        exit(0);
    }

    pid_t child_pid = fork();
    pid_t pid;
    int status;
    if(child_pid >= 0){
        if(child_pid == 0){ // child process
            std::cout << "Child Process " << std::endl;
            pid = getpid();
            printf("Child: %d\n", pid);
            if (-1 == execvp( *args, args)){
                perror("Can't execute");
                exit(1);
            }
        }else{ // parent process
            std::cout << "Parent Process" << std::endl;
            pid = wait(&status);
            if (WIFEXITED(status)){
                printf("Parent: Child exited with status %d\n", WEXITSTATUS(status));
            }
            // waitpid( child_pid, &status, 0);
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
    std::cout << "Command Destructor Called " << std::endl;
    while (*args != NULL){
        delete [] *args++;
    }
}

