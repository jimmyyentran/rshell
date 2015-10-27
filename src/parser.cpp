#include <stdio.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include "connectorsList.cpp"
#include "header/runner.h"
#include "header/parser.h"

const char Parser::KEYS[] = "&|;#";

Parser::Parser(char * str){
    std::cout << "str: " << str << std::endl;
    char * stepper = str;
    size_t i =  strcspn (str, KEYS);

    // single command
    if ( str[i] == '\0' ){
        runners.push_back(convertToCommand(str));
    }

    // multi command
    stepper = &(str[i]);
    std::cout << "stepper: " << stepper << std::endl;
}

Connector* Parser::convertToConnector(char * str){
    if(*str == '&'){
        if(*(++str) == '&'){
            //make & connector
            return new AndConnector();
        }
    } else if (*str == '|'){
        if(*(++str) == '|'){
            //make || connector
            return new OrConnector();
        }
    } else if (*str == ';'){
        // make ; connector
        return new SemicolonConnector();
    } else { // equals to # comment
        // make # connector
    }
    return NULL;
}

std::vector<Runner*>& Parser::getRunners(){
    return runners;
}

void Parser::runRunners(){
    runners.front()->run(true);
    delete runners.front();
}

// str returns from shell and will go out of scope...should new a new char
Command* Parser::convertToCommand(char * str){
    char ** argv = new char*[30];
    parseArgs(str, argv);
    return new Command(argv);
}

void Parser::parseArgs(char * str, char** argv){
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
}

Parser::~Parser(){
    // std::cout << "Parser Destructor Called" << std::endl;
}


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
    // std::cout << pch << std::endl;
    // int i = strcspn (pch, KEYS);
    // std::cout << "find at pos: " << i << std::endl;
    // char substr[100];
    // strncpy (substr, pch, i);
    // if(scanSupported(substr) >= 0){
    // std::cout << "Found matching: " << substr << std::endl;
    // // return something
    // } else {
    // std::cout << "No Match for " << substr << std::endl;
    // }
    // return something

    // if ( i == strlen(pch) ){
    // std::cout << "No conditionals found" << std::endl;
    // }
}

void Parser::test(){
}
