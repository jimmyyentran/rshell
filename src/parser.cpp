#include <stdio.h>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <stdexcept>
#include "header/connectorClasses.h"
#include "header/parser.h"

const char Parser::KEYS[] = "&|;#()";

Parser::Parser(char * str){
    strncpy(cmd, str, Shell::MAX_INPUT2);
}

void Parser::parserInit(){
    char * stepper = cmd;
    int parens = 0;

    size_t i = strcspn(stepper, KEYS);
    bool lastPush = 0; // 1 for command; 0 for connector

    while (stepper[i] != '\0'){
        if(lastPush){ // if last push was a command, quit
            // throw std::invalid_argument(std::string("Parse Error at4: ") + stepper);
        }else {
            char command[COMMAND_LENGTH];
            memcpy(command, stepper, i);
            command[i] = '\0';
            Command* cmdPtr = convertToCommand(command);

            // if valid command, push
            if(cmdPtr != NULL){
                runners.push_back(cmdPtr);
                lastPush = 1;
            }
            // stepper = &(stepper[i]);
        }
        stepper = &(stepper[i]);

        // prevents double connectors
        if(lastPush){ //last push was a command
            switch (*stepper++){
                case '&':
                    if(*stepper++ == '&'){
                        runners.push_back(convertToConnector((char*)"&&"));
                        lastPush = 0;
                    } else {
                        throw std::invalid_argument("Parse error: single & not supported");
                    }
                    break;
                case '|':
                    if(*stepper++ == '|'){
                        runners.push_back(convertToConnector((char*)"||"));
                        lastPush = 0;
                    } else {
                        throw std::invalid_argument("Parse error: single | not supported");
                        return;
                    }
                    break;
                case ';':
                    runners.push_back(convertToConnector((char*)";"));
                    lastPush = 0;
                    break;
                case '#':
                    return; // stop taking more inputs
                case ')': // last push remains command
                    if(parens <= 0){
                        goto printerr;
                    }
                    runners.push_back(convertToConnector((char*)")"));
                    parens--;
                    break;
printerr:
                default:
                    // char const * msg = stepper-1;
                    throw std::invalid_argument(std::string("Parse Error at2: ") + (stepper-1));
            }
        } else { //last push was a connector or beginning of input
            switch (*stepper){
                case '#':
                    return;
                case '(': //last push remains connector
                    runners.push_back(convertToConnector((char*)"("));
                    parens++;
                    stepper++;
                    break;
                default:
                    // char const * msg = stepper;
                    throw std::invalid_argument(std::string("Parse Error at: ") + stepper);
            }
        }

        if(*stepper == '\0'){ // connector at end
            switch(*(stepper - 1)){
                case ')':
                    if(parens != 0){
                        throw std::invalid_argument("Parse error: Missing ')'");
                    }
                    return;
                case ';':
                    return;
                default:
                    throw std::invalid_argument("Parse error: Currently no end-of-line connector supported.");
            }
        }
        i = strcspn(stepper, KEYS);
    } // while loops end

    if(parens != 0){
        throw std::invalid_argument("Parse error: Missing ')'");
    }

    if(lastPush){ // if last push was a command, quit
        throw std::invalid_argument(std::string("Parse Error at3: ") + stepper);
    }
    char commandLast[COMMAND_LENGTH];
    memcpy(commandLast, stepper, i);
    commandLast[i] = '\0';
    // vector doesn't push back NULL
    runners.push_back(convertToCommand(commandLast));
}

Connector* Parser::convertToConnector(const char * str){
    if(strcmp(str, "&&") == 0){
        return new AndConnector();
    } else if (strcmp(str, "||") == 0){
        return new OrConnector();
    } else if (strcmp(str, ";") == 0){
        return new SemicolonConnector();
    } else if (strcmp(str, "(") == 0){ // # poundA
        return new ParenthesisConnector(1);
    } else if (strcmp(str, ")") == 0){ // # poundA
        return new ParenthesisConnector(0);
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

bool Parser::runRunners2(){
    bool commandVal= true;
    bool connectorVal = true;
    for (std::vector<Runner*>::iterator it = runners.begin(); it != runners.end(); ++it) {
        if(dynamic_cast<Command*>(*it)){
            if(connectorVal){
                commandVal = (*it)->run(connectorVal);
            }
        } else {
            if(strcmp((*it)->getName(),"(") == 0){
                if(connectorVal){
                    commandVal = runParenthesis(it, true);
                    continue;
                } else {
                    runParenthesis(it, false);
                    continue;
                }
            }
            connectorVal = (*it)->run(commandVal);
        }
    }
    return false;
}

bool Parser::runParenthesis(std::vector<Runner*>::iterator & it, bool b){
    bool commandVal= true;
    bool connectorVal = b;
    ++it;
    for(; strcmp((*it)->getName(),")") != 0; ++it){
        if(dynamic_cast<Command*>(*it)){
            if(connectorVal){
                commandVal = (*it)->run(connectorVal);
            }
        } else {
            if(strcmp((*it)->getName(),"(") == 0){
                if(connectorVal){
                    commandVal = runParenthesis(it, true);
                    continue;
                }else {
                    runParenthesis(it, false);
                    continue;
                }
            }
            if(b){
                connectorVal = (*it)->run(commandVal);
            }
        }
    }
    // commandVal ? std::cout << "TRUE" : std::cout << "FALSE";
    // std::cout << std::endl;
    return commandVal;
}

// converts string to a command unless the string is empty return NULL
Command* Parser::convertToCommand(char * str){
    char * argv[30];
    *argv = str;
    parseArgs(*argv, argv);
    if(*argv == '\0'){
        return NULL;
    }

    return new Command(argv);
}

// Doesn't take in spaces at beginning
void Parser::parseArgs(char * str, char** argv){
    while (*str != '\0'){
        while (*str == ' ' || *str == '\t' || *str == '\n') {
            *str++ = '\0';
        }
        if(*str != '\0'){ // don't add null elements
            *argv++ = str;
        }
        while (*str != '\0' && *str != ' ' && *str != '\t' && *str != '\n'){
            str++;
        }
    }
    *argv = '\0';
}

Parser::~Parser(){
    for (unsigned i = 0; i < runners.size(); ++i) {
        delete runners[i];
    }
    runners.clear();
}

void Parser::test(){
    if(runners.empty()){
        return;
    }
    for (std::vector<Runner*>::iterator it = runners.begin(); it != runners.end(); ++it) {
        (*it)->print();
    }
}
