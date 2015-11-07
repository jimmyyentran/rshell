#include <iostream>
#include <unistd.h>
#include <cstdio>
#include <sys/wait.h>
#include <cstring>
#include <cstdlib>
#include "header/command.h"
#include "header/parser.h"


Command::Command(char ** cmd){
    unsigned i = 0;
    for(;*cmd != NULL ; ++cmd, ++i){
        char * arg = new char [Parser::COMMAND_LENGTH];
        strncpy(arg, *cmd, Parser::COMMAND_LENGTH);
        args[i] = arg;
    }
    args[i] = NULL;
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
    // std::cout << "Command Destructor Called " << std::endl;
    //delete new allocated arrays
    for(unsigned i = 0; args[i] != NULL ; ++i){
        delete [] args[i];
    }
}

