#include "header/shell.h"
#include "header/log.h"

int main(int argc, char* argv[])
{
    FILELog::ReportingLevel() = FILELog::FromString(argv[1] ? argv[1] : "INFO");

    Shell* shell = new Shell();
    shell->startShell();

    return 0;
}

