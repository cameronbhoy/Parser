#pragma once

#include <iostream>
#include <string>
#include "Scanner.h"
#include "AST.h"
using namespace std;



class Parser
{
public:
    Parser(string fname);
    ASTProgram * parse();

    void printError(string code, string message, int line);

    void rdpProgram();
    ASTFunction* rdpFunction();
    ASTParam* rdpParam();
    bool getErrorDetected();
    ASTNode * rdpTypeList();

    ASTStatements * rdpStatements();
    ASTstatement *rdpStatement();
    ASTif * rdpIf();
    ASTfor *rdpFor();
    ASTreturn * rdpReturn();
    ASTdeclaration *rdpDeclaration(bool firstIdenScannedAlready);
    ASTassign *rdpAssign(bool firstIdenAlreadyScanned);
    ASTfunctionCall *rdpFunctionCall();
    ASTmultipleReturn *rdpMultipleReturn();
    ASTblockStatement *rdpBlockStatement();
    ASTbooleanExprA *rdpBooleanExprA();
    ASTbooleanExprB *rdpBooleanExprB();
    ASTterm *rdpTerm();
    ASTexpr *rdpExpr();
    ASTpow *rdpPow();
    ASTfactor *rdpFactor();
    ASTelement *rdpElement();
private:
    bool errorDetected;
    Scanner* scan;
    ASTProgram * program;


    ASTargs *rdpArgs();
};