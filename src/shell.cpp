#include <iostream>
#include <unistd.h>
#include <cstdio>
#include "header/shell.h"
#include "header/parser.h"
#include <sys/wait.h>

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
//    char input[MAX_INPUT2];
    std::cout << "Start Shell!" << std::endl;
    printPrompt();
    run();
//    std::cin.getline(input, MAX_INPUT2);
//    Parser parser = Parser(input);
//    parser.test();
}

void Shell::run() {
	char* argv[10];
	argv[0] = (char*)"ls";
	argv[1] = NULL;
	pid_t child_pid = fork();
	if(child_pid >= 0){
		if(child_pid == 0){ // child process
			std::cout << "Child Process " << std::endl;
			if (-1 == execvp( *argv , argv)){
				perror("Can't execute");
			}
		} else { // parent process
			std::cout << "Parent Process" << std::endl;
			int status;
			waitpid( child_pid, &status, 0);
		}

	} else {
		perror("Forking error");
	}
}
