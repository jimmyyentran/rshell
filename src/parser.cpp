#ifndef _PARSER_
#define _PARSER_

#include <cstring>
#include <stdio.h>
#include <iostream>

class Parser {
    private:
    public:
        Parser(char * str){
            std::cout << "Start Parsing" << std::endl;
            char delims[5] = " ";
            char* pch = strtok (str, delims);
            while (pch != NULL){
                printf ("%s\n", pch);
                pch = strtok(NULL, delims);
            }
        }

        void test(){
            std::cout << "testing" << std::endl;
        }
};

#endif
