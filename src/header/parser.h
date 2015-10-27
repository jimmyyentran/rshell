#ifndef _PARSER_
#define _PARSER_

#include "command.h"
#include "connector.h"
#include <queue>

class Parser {
    private:
        const static char KEYS[];
        void parseToken(char* pch);
        void parseTokenSimple(char * tkn);
        void parseArgs(char*, char**);
        Command* convertToCommand(char*);
        Connector* convertToConnector(char * str);
        std::vector<Runner*> runners;
    public:
        Parser(char * str);
        ~Parser();
        void test();
        void runRunners();
        std::vector<Runner*>& getRunners();
};

#endif
