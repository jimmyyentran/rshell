#ifndef _PARSER_
#define _PARSER_

#include "command.h"
#include <queue>

class Parser {
    private:
        const static char* EXEC[];
        const static char KEYS[];
        std::queue<Runner*> runners;
        void parseToken(char* pch);
        void parseTokenSimple(char * tkn);
        int scanSupported(const char* exec);
        // Command* convertToObj(char*);
        Command* convertToObj(char*, char**);
    public:
        Parser();
        Parser(char * str);
        void test();
        const std::queue<Runner*>& getRunners();
};

#endif
