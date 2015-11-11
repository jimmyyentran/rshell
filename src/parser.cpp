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

    size_t i = strcspn(stepper, KEYS);
    bool lastPush = 0; // 1 for command; 0 for connector

    while (stepper[i] != '\0'){
        char command[COMMAND_LENGTH];
        memcpy(command, stepper, i);
        command[i] = '\0';
        Command* cmdPtr = convertToCommand(command);

        // if valid command, push
        if(cmdPtr != NULL){
            runners.push_back(cmdPtr);
            lastPush = 1;
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
                case '(':
                    runners.push_back(convertToConnector((char*)"("));
                    std::cout << "found (" << std::endl;
                    break;
                case ')':
                    runners.push_back(convertToConnector((char*)")"));
                    std::cout << "found )" << std::endl;
                    break;
                default:
                    std::cout << "Internal error" << std::endl;
                    exit(1);
                    break;
            }
        } else { //last push was a connector or beginning of input
            switch (*stepper){
                case '#':
                    return;
                default:
                    char const * msg = stepper;
                    throw std::invalid_argument(std::string("Parse Error at: ") + msg);
            }
            // if(stepper[i] == '#'){
            // if(*stepper == '#'){
            // return;
            // }else { // bash doesn't allow beginning and adjacent connectors
            // char const * msg = stepper;
            // throw std::invalid_argument(std::string("Parse Error at: ") + msg);
            // }
        }

        if(*stepper == '\0'){ // connector at end
            throw std::invalid_argument("Parse error: Currently no end-of-line connector supported.");
        }

        i = strcspn(stepper, KEYS);
        }

        char commandLast[COMMAND_LENGTH];
        memcpy(commandLast, stepper, i);
        commandLast[i] = '\0';
        runners.push_back(convertToCommand(commandLast));
    }

    Connector* Parser::convertToConnector(const char * str){
        if(strcmp(str, "&&") == 0){
            return new AndConnector();
        } else if (strcmp(str, "||") == 0){
            return new OrConnector();
        } else if (strcmp(str, ";") == 0){
            return new SemicolonConnector();
        } else if (strcmp(str, "(") == 0 || strcmp(str, ")")){ // # poundA
            // return new OpenParenConnector();

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
                // If previous onnector returns true then run. We don't want to run
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
