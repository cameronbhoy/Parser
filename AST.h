#pragma once

#include <vector>
#include <string>
using namespace std;

/*
 *
 * ASTFunction, ASTNode, ASTProgram, ASTParam compliments of Dr. Benjamin Mood of Point Loma Nazarene University
 *
 */

class ASTFunction;
class ASTNode;
class ASTProgram;
class ASTParam;
class ASTstatement;
class ASTStatements;
class ASTargs;
class ASTfor;
class ASTif;
class ASTassign;
class ASTreturn;
class ASTdeclaration;
class ASTfunctionCall;
class ASTblockStatement;
class ASTmultipleReturn;
class ASTbooleanExprA;
class ASTbooleanExprB;
class ASTterm;
class ASTexpr;
class ASTpow;
class ASTfactor;
class ASTelement;


class ASTNode
{
public:
    virtual void print(int depth) = 0;

private:

};


class ASTProgram : public ASTNode
{
public:
    ASTProgram();
    void addFunction(ASTFunction* theFunction);

    void print(int depth);

private:
    vector<ASTFunction*> functions;
};


class ASTFunction : public ASTNode
{
public:
    ASTFunction(string namein, ASTNode * returnType);
    void addParams(ASTParam* theParams);
    void addStmts(ASTStatements *stmts);
    void print(int depth);
private:
    string name;
    ASTNode * returnType;
    ASTParam* params;
    ASTStatements* stmts;

};


class ASTParam : public ASTNode
{
public:
    ASTParam();
    void addParam(string name, string type);
    void print(int depth);
private:
    vector<string> varNames;
    vector<string> types;
};


class ASTStatements : public ASTNode
{
public:
    ASTStatements();
    void addStmt(ASTstatement * stmt_in);
    void print(int depth);
    void addIden(string iden);
private:
    vector<ASTstatement *> stmts;
    string iden;

};


class ASTTypeList : public ASTNode {
public:
    ASTTypeList(vector<string> typesIn);
    void print(int depth);
private:
    vector<string> theTypes;
};


class ASTstatement : public ASTNode
{
public:
    ASTstatement(string name, string type);
    void addIf(ASTif * ifStmt);
    void addFor(ASTfor * forStmt);
    void addReturn(ASTreturn * theReturn);
    void addDeclaration(ASTdeclaration * declarationStmt);
    void print(int depth);
    void addAssign(ASTassign *assignStmt);
    void addFunctionCall(ASTfunctionCall *functionCall);
    void addMultipleReturn(ASTmultipleReturn *multipleReturn);
    void addBlockStatement(ASTblockStatement *block);
private:
    string name;
    string type;
    ASTif * theIf;
    ASTfor * theFor;
    ASTreturn * theReturn;
    ASTdeclaration * declaration;
    ASTassign * assign;
    ASTfunctionCall * functionCall;
    ASTmultipleReturn * multipleReturn;
    ASTblockStatement * block;



};


class ASTargs : public ASTNode
{
public:
    ASTargs();
    void print(int depth);
    void addBoolA(ASTbooleanExprA * boolA);
private:
    vector<ASTbooleanExprA *> boolA;
};


class ASTfor : public ASTNode
{
public:
    ASTfor();
    void print(int depth);
    void addBoolA(ASTbooleanExprA *boolA);
    void addAssign(ASTassign *assign);
    void addDeclaration(ASTdeclaration * declaration);
    void addStatement(ASTstatement *pTstatement);

private:
    ASTassign * assign;
    ASTbooleanExprA * boolA;
    ASTstatement * statement;
    ASTdeclaration * declaration;
};


class ASTif : public ASTNode
{
public:
    ASTif();
    void print(int depth);
    void addStatement(ASTstatement *stmt);
    void addBoolA(ASTbooleanExprA *boolA);
    void addStatements(ASTStatements * stmts);
    ASTbooleanExprA *getBoolA();
private:
    ASTstatement * statement;
    ASTbooleanExprA * boolA;
    ASTStatements * statements;
};


class ASTassign : public ASTNode
{
public:
    ASTassign();
    void print(int depth);
    void addIden(string iden);
    void addBoolExprA(ASTbooleanExprA * boolA);
private:
    ASTbooleanExprA * boolA;
    string iden;
};


class ASTreturn : public ASTNode
{
public:
    ASTreturn();
    void print(int depth);
    void addBoolA(ASTbooleanExprA * boolA);
    void adjustOptions(bool optionsAdded);

private:
    vector<ASTbooleanExprA *> boolA;
    bool optionalsAdded;
};


class ASTfunctionCall : public ASTNode
{
public:
    ASTfunctionCall();
    void print(int depth);
    void addIden(string basicString);
    void addArgs(ASTargs * args);
private:
    string iden;
    ASTargs * args;
};


class ASTblockStatement : public ASTNode
{
public:
    ASTblockStatement();
    void print(int depth);
    void addStatements(ASTStatements *statements);
private:
    ASTStatements * statements;

};


class ASTdeclaration : public ASTNode
{
public:
    ASTdeclaration();
    //ASTdeclaration(string iden1, string iden2);

    void print(int depth);
    void addBoolExprA(ASTbooleanExprA * boolA);
    void addIden(string iden);
    void adjustOptions(bool optionsAdded);
private:
    vector<string> idens;
    //string iden2;
    ASTbooleanExprA * boolA;
    bool optionalsAdded;

};


class ASTmultipleReturn : public ASTNode
{
public:
    ASTmultipleReturn();
    void addIden(string iden);
    void print(int depth);
    void addFunctionCall(ASTfunctionCall *functionCall);
private:
    vector<string> idens;
    ASTfunctionCall * functionCall;

};


class ASTbooleanExprA : public ASTNode
{
public:
    ASTbooleanExprA();
    void print(int depth);

    void addOperator(string operatorIn);
    void addBoolExprB(ASTbooleanExprB *boolB);
    void adjustOptions(bool optionsAdded);
private:
    vector<ASTbooleanExprB *> boolB;
    vector<string> operators;
    bool optionalsAdded;
};


class ASTbooleanExprB : public ASTNode
{
public:
    ASTbooleanExprB();
    void print(int depth);
    void addTerm(ASTterm * term);
    void addOperator(string operatorIn);
private:
    vector<ASTterm *> terms;
    vector<string> operators;
};


class ASTterm : public ASTNode
{
public:
    ASTterm();
    void print(int depth);
    void addExpr(ASTexpr * expr);
    void addOperator(string operatorIn);
private:
    vector<ASTexpr *> exprs;
    vector<string> operators;
};


class ASTexpr : public ASTNode
{
public:
    ASTexpr();
    void print(int depth);
    void addPow(ASTpow * pow);
    void addOperator(string operatorIn);
private:
    vector<ASTpow *> pows;
    vector<string> operators;
};


class ASTpow : public ASTNode
{
public:
    ASTpow();
    void print(int depth);
    void addFactor(ASTfactor * factor);
private:
    vector<ASTfactor *> factors;
};


class ASTfactor : public ASTNode
{
public:
    ASTfactor();
    void print(int depth);
    void addBoolA(ASTbooleanExprA * boolA);
    void addElement(ASTelement * element);
private:
    ASTbooleanExprA * boolA;
    ASTelement * element;
    bool factorHasElement;
};


class ASTelement : public ASTNode
{
public:
    ASTelement();
    void print(int depth);
    void addFunctionCall(ASTfunctionCall * functionCall);
    void addIden(string iden);
    void addConst(int constant);
    void addType(string type);
private:
    ASTfunctionCall * functionCall;
    string type;
    string iden;
    int constant;
};