#include <iostream>
#include "header/shell.h"

int main(int argc, char* argv[])
{
    Shell* shell = new Shell();
    shell->startShell();
    return 0;
}

