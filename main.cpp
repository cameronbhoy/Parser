#include "Scanner.h"
#include "Parser.h"

/*
 *
 * main.cpp compliments of Dr. Benjamin Mood of Point Loma Nazarene University
 *
 */

#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "Usage: <executable name> <filename>";
    }

    Parser p(argv[1]);
    ASTProgram * prog = p.parse();
    if (!p.getErrorDetected())
    {
        prog->print(0);
    }

}
