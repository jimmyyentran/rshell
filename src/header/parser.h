#ifndef _PARSER_
#define _PARSER_

#include "command.h"
#include <queue>

class Parser {
    private:
        const static char* EXEC[];
        const static char KEYS[];
        void parseToken(char* pch);
        void parseTokenSimple(char * tkn);
        int scanSupported(const char* exec);
        // Command* convertToObj(char*);
        void convertToObj(char*, char**);
        std::queue<Runner*> runners;
    public:
        Parser(char * str);
        ~Parser();
        void test();
        std::queue<Runner*>& getRunners();
        void runRunners();
};

#endif
