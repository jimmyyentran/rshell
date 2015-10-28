#include <stdio.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <cstdlib>
#include "connectorsList.cpp"
#include "header/runner.h"
#include "header/parser.h"

const char Parser::KEYS[] = "&|;#";

Parser::Parser(char * stepper){
    // char * stepper = str;
    // stepper = str;
    std::cout << stepper << std::endl;
    size_t i = strcspn(stepper, KEYS);
    while (stepper[i] != '\0'){
        char * command = new char[30];
        strncpy(command, stepper, i);
        runners.push_back(convertToCommand(command));
        stepper = &(stepper[i]);
        switch (*stepper++){
            case '&':
                if(*stepper++ == '&'){
                    runners.push_back(convertToConnector((char*)"&&"));
                } else {
                    std::cout << "Parse error single & not supported" << std::endl;
                    return;
                }
                break;
            case '|':
                if(*stepper++ == '|'){
                    runners.push_back(convertToConnector((char*)"||"));
                } else {
                    std::cout << "Parse error single | not supported" << std::endl;
                    return;
                }
                break;
            case ';':
                runners.push_back(convertToConnector((char*)";"));
                break;
            case '#':
                return;
            default:
                std::cout << "Internal eror" << std::endl;
                exit(1);
                break;
        }
        if(*stepper == '\0'){ // connector at end
            printf("%s\n", "end of string");
            return;
        }
        i = strcspn(stepper, KEYS);
    }
    char* command = new char[30];
    strcpy(command, stepper);
    runners.push_back(convertToCommand(command));
}

Connector* Parser::convertToConnector(const char * str){
    if(strcmp(str, "&&") == 0){
        // printf("%s\n", "And");
        return new AndConnector();
    } else if (strcmp(str, "||") == 0){
        // printf("%s\n", "Or");
        return new OrConnector();
    } else if (strcmp(str, ";") == 0){
        // printf("%s\n", "Semi");
        return new SemicolonConnector();
    } else { // # pound

    }
    printf("%s\n", "error");
    return NULL;
}

std::vector<Runner*>& Parser::getRunners(){
    return runners;
}

void Parser::runRunners(){
    bool commandVal= true;
    bool connectorVal = true;
    for (std::vector<Runner*>::iterator it = runners.begin(); it != runners.end(); ++it) {
        if(dynamic_cast<Command*>(*it)){
            // If previous connector returns true then run. We don't want to run
            // commands with a false input value because it might
            // change our preserved value from the last run.
            // This renders the run(bool) boolean parameter useless because we will
            // only call run whenever parameter is true. However polymorphism
            // requires the parameter.
            if(connectorVal){
                commandVal = (*it)->run(connectorVal);
            }
        } else {
            connectorVal = (*it)->run(commandVal);
        }
    }
}

// str returns from shell and will go out of scope...should new a new char
Command* Parser::convertToCommand(char * str){
    char ** argv = new char*[30];
    parseArgs(str, argv);
    return new Command(argv);
}

// TODO:should be const str
void Parser::parseArgs(char * str, char** argv){
    while (*str != '\0'){
        while (*str == ' ' || *str == '\t' || *str == '\n') {
            *str++ = '\0';
        }
        if(*str != '\0'){ // don't add null elements
            *argv++ = str;
        }
        // *argv++ = str;
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

void Parser::test(){
    for (std::vector<Runner*>::iterator it = runners.begin(); it != runners.end(); ++it) {
        printf("%s", "Element: ");
        (*it)->print();
    }
}
