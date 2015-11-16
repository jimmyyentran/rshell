#ifndef _PARSER_
#define _PARSER_

#include "command.h"
#include "connector.h"
#include "shell.h"
#include "runner.h"
#include <queue>

class Parser {
    private:
        char cmd[500];
        const static char KEYS[];

        void parseArgs(char*, char**);
        Command* convertToCommand(char*);
        Connector* convertToConnector(const char * str);
        std::vector<Runner*> runners;
        bool runParenthesis(std::vector<Runner*>::iterator&, bool b);
        void checkParens(int);
    public:
        const static int COMMAND_LENGTH = 100;
        Parser(char * str);
        ~Parser();
        void test();
        void runRunners();
        bool runRunners2();
        std::vector<Runner*>& getRunners();
        void parserInit();
};

#endif
