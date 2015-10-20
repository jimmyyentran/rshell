#include <iostream>
#include "shell.cpp"
using namespace std;

int main(int argc, char* argv[])
{
    Shell* shell = new Shell();
    shell->startShell();
    cout << "Hello World!" << endl;
    return 0;
}

