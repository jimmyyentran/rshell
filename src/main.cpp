#include "header/shell.h"

int main(int argc, char* argv[])
{
    Shell* shell = new Shell(argv[1] ? argv[1] : "NORMAL");
    shell->startShell();
    delete shell;
    return 0;
}

