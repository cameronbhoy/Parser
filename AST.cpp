#include "AST.h"
#include <iostream>
#include <string>

/*
 *
 * functions belonging to the classes ASTFunction, ASTNode, ASTProgram, ASTParam compliments
 * of Dr. Benjamin Mood of Point Loma Nazarene University
 *
 */

using namespace std;
static int langDepth = 0;
//AST Program
ASTProgram::ASTProgram()
{

}

void ASTProgram::addFunction(ASTFunction* theFunction)
{
    functions.push_back(theFunction);
}

void ASTProgram::print(int depth)
{
    for (int i = 0; i < functions.size(); i++)
    {
        functions[i]->print(0);
    }
}


//AST Function
ASTFunction::ASTFunction(string namein, ASTNode * returnTypein)
{
    name = namein;
    returnType = returnTypein;
    params = NULL;
    stmts = NULL;
}

void ASTFunction::addParams(ASTParam* params)
{
    this->params = params;
}

void ASTFunction::addStmts(ASTStatements * stmts)
{
    this->stmts = stmts;
}

void ASTFunction::print(int depth)
{
    returnType -> print(0);
    cout << name << "(";
    if (params != NULL)
    {
        params->print(0);
    }
    cout << ")\n{";

    stmts->print(1);

    cout << "\n}";
}


//AST Param
ASTParam::ASTParam()
{

}
void ASTParam::addParam(string namein, string typein)
{
    varNames.push_back(namein);
    types.push_back(typein);
}

void ASTParam::print(int depth)
{
    for (int i = 0; i < varNames.size(); i++)
    {
        cout << types[i] << " " << varNames[i];
        if (i != varNames.size() - 1)
        {
            cout << ", ";
        }
    }
}


//AST Statements
ASTStatements::ASTStatements()  {
    iden = "";
}

void ASTStatements::addStmt(ASTstatement * stmt_in) {
    stmts.push_back(stmt_in);
}

void ASTStatements::addIden(string iden) {
    this -> iden = iden;
}

void ASTStatements::print(int depth) {
    for(int i = 0; i < stmts.size(); i++) {
        cout << "\n\t";
        stmts.at(i)->print(stmts.size());
        cout << "\n";
    }
}

//AST TypeList
ASTTypeList::ASTTypeList(vector<string> theStrings) {
    theTypes = theStrings;
}

void ASTTypeList::print(int depth) {
    for(int i = 0; i < theTypes.size(); i++) {
        cout << theTypes[i] << " ";
        if(theTypes.size()-1 != i) {
            cout << ", ";
        }
    }
}


//AST Statement
ASTstatement::ASTstatement(string name, string type) {
    this -> name = name;
    this -> type = type;
    theIf = NULL;
    theFor = NULL;
    theReturn = NULL;
    declaration = NULL;
    assign = NULL;
    functionCall = NULL;
    multipleReturn = NULL;
    block = NULL;
}

void ASTstatement::addIf(ASTif * ifStmt) {
    theIf = ifStmt;
}

void ASTstatement::addFor(ASTfor * forStmt) {
    theFor = forStmt;
}

void ASTstatement::addReturn(ASTreturn * returnStmt) {
    theReturn = returnStmt;
}

void ASTstatement::addDeclaration(ASTdeclaration  * declarationStmt) {
    declaration = declarationStmt;
}

void ASTstatement::addAssign(ASTassign * assignStmt) {
    assign = assignStmt;
}

void ASTstatement::addFunctionCall(ASTfunctionCall * functionCall) {
    this->functionCall = functionCall;
}

void ASTstatement::addMultipleReturn(ASTmultipleReturn * multipleReturn) {
    this->multipleReturn = multipleReturn;
}

void ASTstatement::addBlockStatement(ASTblockStatement * block) {
    this->block = block;
}

void ASTstatement::print(int depth) {
    if(type == "if") {
        theIf->print(1);
    } else if(type == "for") {
        theFor->print(1);
    } else if(type == "return") {
        theReturn->print(1);
    } else if(type == "declaration") {
        declaration->print(1);
    } else if(type == "assign") {
        assign->print(1);
    } else if(type == "functionCall") {
        functionCall->print(1);
    } else if(type == "multipleReturn") {
        multipleReturn->print(1);
    } else if(type == "block") {
        block->print(1);
    }
}

//AST if
ASTif::ASTif() {
    statement = NULL;
    boolA = NULL;
}

void ASTif::print(int depth) {
    cout << "if (";
    boolA->print(1);
    cout << ") \n\t";
    statement->print(1);
    cout << "\n";
};

void ASTif::addStatement(ASTstatement * stmt) {
    statement = stmt;
}

void ASTif::addBoolA(ASTbooleanExprA * boolA) {
    this -> boolA = boolA;
}

ASTbooleanExprA * ASTif::getBoolA() {
    return boolA;
}

void ASTif::addStatements(ASTStatements * stmts) {
    statements = stmts;
}

//AST for
ASTfor::ASTfor() {
    declaration = NULL;
    assign = NULL;
    boolA = NULL;
    statement = NULL;
}

void ASTfor::addAssign(ASTassign * assign) {
    this -> assign = assign;
}

void ASTfor::addBoolA(ASTbooleanExprA * boolA) {
    this -> boolA = boolA;
}

void ASTfor::addStatement(ASTstatement * statement) {
    this -> statement = statement;
}

void ASTfor::addDeclaration(ASTdeclaration *declaration) {
    this -> declaration = declaration;
}

void ASTfor::print(int depth) {
    cout << "for (";
    declaration -> print(depth);
    boolA -> print(depth);
    cout << "; ";
    assign -> print(depth);
    cout << " ) {\n\t";
    statement->print(depth);
    cout << "\n}";
}

//AST declaration
ASTdeclaration::ASTdeclaration() {
    boolA = NULL;
    optionalsAdded = false;
}

void ASTdeclaration::addIden(string iden) {
    idens.push_back(iden);
}

void ASTdeclaration::addBoolExprA(ASTbooleanExprA * boolA) {
    this -> boolA = boolA;
}

void ASTdeclaration::adjustOptions(bool optionsAdded) {
    this->optionalsAdded = optionsAdded;
}

void ASTdeclaration::print(int depth) {
    cout << idens.at(0) << " " << idens.at(1);
    if(optionalsAdded) {
        cout << " = ";
        boolA->print(1);
    }
    cout << "; ";
}

//AST multiple return
ASTmultipleReturn::ASTmultipleReturn() {
    functionCall = NULL;
}

void ASTmultipleReturn::addIden(string iden) {
    idens.push_back(iden);
}

void ASTmultipleReturn::addFunctionCall(ASTfunctionCall * functionCall) {
    this -> functionCall = functionCall;
}

void ASTmultipleReturn::print(int depth) {
    cout << "return " << idens.at(0);

    for(int i = 1; i < idens.size(); i++) {
        cout << ", " << idens.at(i);
    }

    cout << " = " ;

    functionCall->print(1);

    cout << ";";
}

//BOOL EXPR A
ASTbooleanExprA::ASTbooleanExprA() {
    optionalsAdded = false;
}

void ASTbooleanExprA::addOperator(string operatorIn) {
    operators.push_back(operatorIn);
}

void ASTbooleanExprA::addBoolExprB(ASTbooleanExprB * boolBIn) {
    boolB.push_back(boolBIn);
}

void ASTbooleanExprA::adjustOptions(bool optionsAdded) {
    this->optionalsAdded = optionsAdded;
}

void ASTbooleanExprA::print(int depth) {
   boolB.at(0)->print(1);

   if(optionalsAdded) {
       for(int i = 0; i < boolB.size()-1; i++) {
           cout << " " << operators.at(i) << " " << boolB.at(i+1); //may have issue
       }
   }
}

//BOOL EXPR B
ASTbooleanExprB::ASTbooleanExprB() {

}

void ASTbooleanExprB::addTerm(ASTterm *term_in) {
    terms.push_back(term_in);
}

void ASTbooleanExprB::addOperator(string operatorIn) {
    operators.push_back(operatorIn);
}

void ASTbooleanExprB::print(int depth) {
    terms.at(0) -> print(1);

    if(operators.size() > 0) {
        for(int i = 0; i < terms.size()-1; i++) {
            cout << " " << operators.at(i) << " ";
            terms.at(i+1) -> print(1); //may have issue
        }
    }
}

//AST block statement
ASTblockStatement::ASTblockStatement() {
    statements = NULL;
}

void ASTblockStatement::addStatements(ASTStatements * statements) {
    this -> statements = statements;
}

void ASTblockStatement::print(int depth) {
    cout << "{\n\t";
    statements ->print(1);
    cout << "\n}";
}

//AST assign
ASTassign::ASTassign() {
    boolA = NULL;
}

void ASTassign::addBoolExprA(ASTbooleanExprA * boolA) {
    this -> boolA = boolA;
}

void ASTassign::addIden(string iden) {
    this->iden = iden;
}

void ASTassign::print(int depth) {
    cout << iden << " = ";
    boolA->print(1);
    cout << ";";
}

//AST functionCall
ASTfunctionCall::ASTfunctionCall() {
    iden = "";
    args = NULL;
}

void ASTfunctionCall::addIden(string iden) {
    this->iden = iden;
}

void ASTfunctionCall::print(int depth) {
    cout << iden << " (";

    if(args != NULL) {
        args->print(1);
    }

    cout << ") ";
}

void ASTfunctionCall::addArgs(ASTargs * args) {
    this->args = args;
}

//AST return
ASTreturn::ASTreturn() {
    optionalsAdded = false;
}

void ASTreturn::addBoolA(ASTbooleanExprA *boolA_in) {
    boolA.push_back(boolA_in);
}

void ASTreturn::adjustOptions(bool optionsAdded) {
    this->optionalsAdded = optionsAdded;
}

void ASTreturn::print(int depth) {
    cout << "return ";

    if (boolA.size() == 1) {
        boolA.at(0)->print(1);
    } else if (boolA.size() >1){
        for(int i = 0; i < boolA.size()-1; i++) {
            cout << ", ";
            boolA.at(i) -> print(1);
        }
    }

    cout << ";\n";
}


ASTterm::ASTterm() {

}

void ASTterm::print(int depth) {
    exprs.at(0)->print(1);

    if(exprs.size() > 1) {
        for(int i = 0; i < exprs.size()-1; i++) {
            cout << " " << operators.at(i) << " ";
            exprs.at(i+1)->print(1);
            cout << " ";
        }
    }
}

void ASTterm::addExpr(ASTexpr *expr) {
    exprs.push_back(expr);
}

void ASTterm::addOperator(string operatorIn) {
    operators.push_back(operatorIn);
}


ASTexpr::ASTexpr() {

}

void ASTexpr::print(int depth) {
    pows.at(0)->print(1);

    if(pows.size() > 1) {
        for(int i = 0; i < pows.size()-1; i++) {
            cout << " " << operators.at(i) << " ";
            pows.at(i+1)->print(1);
            cout << " ";
        }
    }
}

void ASTexpr::addPow(ASTpow *pow) {
    pows.push_back(pow);
}

void ASTexpr::addOperator(string operatorIn) {
    operators.push_back(operatorIn);
}


ASTpow::ASTpow() {

}

void ASTpow::print(int depth) {
    factors.at(0)->print(1);

    if(factors.size() > 1) {
        for(int i = 1; i < factors.size(); i++) {
            cout << " pow ";
            factors.at(i)->print(1);
            cout << " ";
        }
    }
}

void ASTpow::addFactor(ASTfactor * factor) {
    factors.push_back(factor);
}


ASTfactor::ASTfactor() {
    boolA = NULL;
    element = NULL;
    factorHasElement = false;
}

void ASTfactor::print(int depth) {
    if(factorHasElement) {
        element->print(1);
    } else {
        cout << " {";
        boolA->print(1);
        cout << "} ";
    }
}

void ASTfactor::addBoolA(ASTbooleanExprA * boolA) {
    this -> boolA = boolA;
}

void ASTfactor::addElement(ASTelement *element) {
    this -> element = element;
    factorHasElement = true;
}


ASTelement::ASTelement() {
    functionCall = NULL;
    type = "";
}

void ASTelement::print(int depth) {
    if(type == "functionCall") {
        functionCall->print(1);
    } else if(type == "iden") {
        cout << " " << iden << " ";
    } else if(type == "constant") {
        cout << " " << constant << " ";
    }
}

void ASTelement::addFunctionCall( ASTfunctionCall * functionCall) {
    this->functionCall = functionCall;
}

void ASTelement::addIden(string iden) {
    this->iden = iden;
}

void ASTelement::addConst(int constant) {
    this->constant = constant;
}

void ASTelement::addType(string type) {
    this->type = type;
}

ASTargs::ASTargs() {

}

void ASTargs::print(int depth) {
    boolA.at(0)->print(1);

    if(boolA.size() > 1) {
        for(int i = 1; i < boolA.size(); i++) {
            cout << ", ";
            boolA.at(i)->print(1);
        }
    }
}

void ASTargs::addBoolA(ASTbooleanExprA * boolA) {
    this->boolA.push_back(boolA);
}
