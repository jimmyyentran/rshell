#include <stdio.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include "header/runner.h"
#include "header/parser.h"

const char* Parser::EXEC[] = {"ls", "echo", NULL};
const char Parser::KEYS[] = "&|;";

Parser::Parser(char * str){
    size_t i =  strcspn (str, KEYS);
    if( i != sizeof(str)) {
        // there is only one command
        char * args[30];
        convertToObj(str, args);
        std::cout << "testingp: " << args[0] << std::endl;
        std::cout << "testingp: " << args[1] << std::endl;
        runners.push(new Command(args));
        std::cout << "pointer: " << &(runners.front()) << std::endl;
        // char cmd[sizeof(str)];
        // strcpy( cmd, pch );
    }

    // while (pch != NULL){
    // // found key
    // std::cout << "Found delim" << std::endl;
    // }
}

const std::queue<Runner*>& Parser::getRunners(){
    std::cout << "getRunner: " << &runners << std::endl;
    return runners;
}

Command* Parser::convertToObj(char * str, char** argv){
    while (*str != '\0'){
        while (*str == ' ' || *str == '\t' || *str == '\n') {
            *str++ = '\0';
        }
        *argv++ = str;
        while (*str != '\0' && *str != ' ' && *str != '\t' && *str != '\n'){
            str++;
        }
    }
    *argv = '\0';
    return new Command(argv);
}


// Parser::Parser(char * str){
// char delims[5] = " ";
// char* pch = strtok (str, delims);
// // parseToken(pch);
// std::cout << "pch: " << pch << std::endl;
// std::cout << "&pch: " << &pch << std::endl;
// parseTokenSimple(pch);
// // while (pch != NULL){
// // // std::cout << &pch << std::endl;
// // std::cout << pch << std::endl;
// // pch = strtok(NULL, delims);
// // }
// }

void Parser::parseTokenSimple(char * tkn){
    std::cout << "tkn: " << tkn << std::endl;
    std::cout << "&tnk: " << &tkn << std::endl;
    ++tkn;
    std::cout << "++tkn: " << tkn << std::endl;
    std::cout << "&tkn: "<< &tkn << std::endl;
}


// Parser::Parser(char * str){
// char delims[5] = " ";
// char* pch = strtok (str, delims);
// parseToken(pch);
// while (pch != NULL){
// printf ("%s\n", pch);
// pch = strtok(NULL, delims);
// }
// }

void Parser::parseToken(char* pch){
    std::cout << pch << std::endl;
    int i = strcspn (pch, KEYS);
    std::cout << "find at pos: " << i << std::endl;
    char substr[100];
    strncpy (substr, pch, i);
    if(scanSupported(substr) >= 0){
        std::cout << "Found matching: " << substr << std::endl;
        // return something
    } else {
        std::cout << "No Match for " << substr << std::endl;
    }
    // return something

    // if ( i == strlen(pch) ){
    // std::cout << "No conditionals found" << std::endl;
    // }
}

int Parser::scanSupported(const char* exec){
    for (unsigned i = 0; EXEC[i] != NULL; ++i){
        if(strcmp (exec, EXEC[i]) == 0){
            return i;
        }
    }
    return -1;
}

void Parser::test(){
}

// const char* Parser::EXEC[] = {"ls"};
