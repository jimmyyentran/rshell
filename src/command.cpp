#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <sys/wait.h>
#include "header/command.h"

Command::Command(char ** cmd){
    args = cmd;
    std::cout << "TEST" << std::endl;
}

bool Command::run() {
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
    std::cout << "command: " << args[0] << std::endl;
    std::cout << "command: " << args[1] << std::endl;
}


