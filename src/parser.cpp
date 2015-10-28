#include <stdio.h>
#include <iostream>
#include <cstring>
#include <vector>
#include <cstdlib>
#include "header/connectorClasses.h"
#include "header/runner.h"
#include "header/parser.h"

const char Parser::KEYS[] = "&|;#";

Parser::Parser(char * stepper){
    size_t i = strcspn(stepper, KEYS);
    bool lastPush = 0; // 1 for command; 0 for connector

    while (stepper[i] != '\0'){
        char * command = new char[30];
        strncpy(command, stepper, i);
        Command* cmdPtr = convertToCommand(command);

        // if valid command, push
        if(cmdPtr != NULL){
            runners.push_back(cmdPtr);
            lastPush = 1;
        }
        stepper = &(stepper[i]);

        // prevents double connectors
        if(lastPush){
            // this is one of the example that shows the power of switch-cases.
            // Switch case holds the value to check before incrementing. If-else
            // doesn't do this
            switch (*stepper++){
                case '&':
                    if(*stepper++ == '&'){
                        runners.push_back(convertToConnector((char*)"&&"));
                        lastPush = 0;
                    } else {
                        std::cout << "Parse error: single & not supported" << std::endl;
                        return;
                    }
                    break;
                case '|':
                    if(*stepper++ == '|'){
                        runners.push_back(convertToConnector((char*)"||"));
                        lastPush = 0;
                    } else {
                        std::cout << "Parse error: single | not supported" << std::endl;
                        return;
                    }
                    break;
                case ';':
                    runners.push_back(convertToConnector((char*)";"));
                    lastPush = 0;
                    break;
                case '#':
                    return; // stop taking more inputs
                default:
                    std::cout << "Internal error" << std::endl;
                    exit(1);
                    break;
            }
        } else {
            if(stepper[i] == '#'){
                return;
            }else { // bash doesn't allow beginning and adjacent connectors
                std::cout << "Parse Error at: " << stepper << std::endl;
                return;
            }
        }

        if(*stepper == '\0'){ // connector at end
            std::cout << "Parse error: Currently no end-of-line connector supported." << std::endl;
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
// converts string to a command unless the string is empty;
Command* Parser::convertToCommand(char * str){
    char ** argv = new char*[30];
    parseArgs(str, argv);
    if(*argv == '\0'){
        return NULL;
    }
    return new Command(argv);
}

// TODO:should be const str
// Doesn't take in spaces at beginning
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

void Parser::test(){
    for (std::vector<Runner*>::iterator it = runners.begin(); it != runners.end(); ++it) {
        (*it)->print();
    }
}
