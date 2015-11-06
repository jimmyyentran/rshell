#ifndef _PARSER_
#define _PARSER_

#include "command.h"
#include "connector.h"
#include <queue>

class Parser {
    private:
        const static char KEYS[];

        void parseArgs(char*, char**);
        Command* convertToCommand(char*);
        Connector* convertToConnector(const char * str);
        std::vector<Runner*> runners;
        char cmd[500];
    public:
        Parser(char * str);
        ~Parser();
        void test();
        void runRunners();
        std::vector<Runner*>& getRunners();
        void parserInit();
};

#endif
