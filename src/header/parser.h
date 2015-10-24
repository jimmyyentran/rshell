#ifndef _PARSER_
#define _PARSER_

class Parser {
    private:
        const static char* EXEC[];
        const static char KEYS[];
        void parseToken(char* pch);
        void parseTokenSimple(char * tkn);
        int scanSupported(const char* exec);
    public:
        Parser();
        Parser(char * str);
        void test();
};

#endif
