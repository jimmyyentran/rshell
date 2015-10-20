#ifndef _PARSER_
#define _PARSER_

#include <cstring>
#include <stdio.h>

class Parser {
    private:
    public:
        Parser(char* str){
            char delims[5] = " ";
            char* pch = strtok (str, delims);
            while (pch != NULL){
                printf ("%s\n", pch);
                pch = strtok(NULL, delims);
            }
        }
};

#endif
