#ifndef _PARSER_
#define _PARSER_

#include "command.h"
#include <queue>

class Parser {
    private:
        const static char KEYS[];
        void parseToken(char* pch);
        void parseTokenSimple(char * tkn);
        // Command* convertToObj(char*);
        void convertToObj(char*, char**);
    public:
        Parser(char * str);
        ~Parser();
        void test();
        void runRunners();
};

#endif
