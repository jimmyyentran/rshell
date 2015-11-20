#ifndef _COMMAND_CLASSES_
#define _COMMAND_CLASSES_

#include <iostream>
#include <unistd.h> //fork, execvp
#include <cstdio> //perror
#include <sys/wait.h> //wait, WIFEXITED, WEXITSTATUS
#include <cstdlib> //exit 
#include <cstring> //strcmp
// #include <sys/types.h>
#include <sys/stat.h>
#include "command.h"

class TestCommand : public Command{
    private:
        bool isBracket;
    public:
        TestCommand(char ** cmd):Command(cmd), isBracket(false){}
        TestCommand(char ** cmd, bool b):Command(cmd), isBracket(b){}

        bool run(bool b){
            pid_t child_pid = fork();
            int status;
            if(child_pid >= 0){
                if(child_pid == 0){ // child process
                    char type = 'e';
                    char** stepper = args;

                    ++stepper;

                    if(*stepper){
                        if(**(stepper) == '-'){
                            switch ( (*stepper)[1] ){
                                case 'e':
                                    break;
                                case 'f':
                                    type = 'f';
                                    break;
                                case 'd':
                                    type = 'd';
                                    break;
                                default:
                                    std::cerr << "Flag not supported" << std::endl;
                                    exit(2);
                            }
                            ++stepper;
                        }
                    }else {
                        std::cerr << "No file to test" << std::endl;
                        exit(2);
                    }

                    struct stat file_info;
                    if(*stepper){
                        if(stat(*stepper, &file_info) == -1){
                            perror("stat");
                            exit(0); //failed to find file
                        }
                    }else {
                        std::cerr << "No file to test" << std::endl;
                        exit(2);
                    }

                    if(*(++stepper)){
                        if(isBracket){
                            if(strcmp(*stepper, "]") != 0){
                                std::cerr << "Too many args" << std::endl;
                                exit(2);
                            }else {
                                std::cerr << "No ']' found" << std::endl;
                                exit(2);
                            }
                        }else {
                            std::cerr << "Too many args" << std::endl;
                            exit(2);
                        }
                    }

                    switch(type){
                        case 'e':
                            exit(1);
                            break;
                        case 'f':
                            exit(S_ISREG(file_info.st_mode));
                        case 'd':
                            exit(S_ISDIR(file_info.st_mode));
                    }

                    exit(0);
                }else{ // parent process
                    wait(&status);
                    if (WIFEXITED(status)){
                        if(status == 256){
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
};

#endif /* ifndef _COMMAND_CLASSES_ */
