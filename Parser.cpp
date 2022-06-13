#include "Parser.h"

// ** printError code compliments of Dr. Benjamin Mood of Point Loma Nazarene University **
void Parser::printError(string code, string message, int line)
{
    cout << code << " on line : " << line << " " << message << ". Recieved " <<  scan->toString(scan->currentTokenType()) <<" \"" << scan->currentTokenString()<<"\"."  << endl;
    errorDetected = true;
}

// ** Parser Constructor code compliments of Dr. Benjamin Mood of Point Loma Nazarene University **
Parser::Parser(string fname)
{
    scan = new Scanner(fname);
}

// ** getErrorDetected code compliments of Dr. Benjamin Mood of Point Loma Nazarene University **
bool Parser::getErrorDetected()
{
    return errorDetected;
}

// ** parse code compliments of Dr. Benjamin Mood of Point Loma Nazarene University **
ASTProgram* Parser::parse()
{
    rdpProgram();
    return program;
}

// ** rdpProgram code compliments of Dr. Benjamin Mood of Point Loma Nazarene University **
void Parser::rdpProgram()
{
    program = new ASTProgram();

    if (scan->currentTokenType() == IDEN)
    {
        program->addFunction(rdpFunction());
    }
    else
    {
        printError("E1", "Expecting IDEN at program beginning", scan->getLine());
    }

    while (scan->currentTokenType() != NONE && !errorDetected)
    {
        program->addFunction(rdpFunction());
    }
}

// ** rdpFunction code compliments of Dr. Benjamin Mood of Point Loma Nazarene University **
ASTFunction* Parser::rdpFunction() {
    ASTFunction *theFunc = NULL;
    string rtype;

    //call typelist
    ASTNode *typeList = rdpTypeList();

    //IDEN
    if (scan->currentTokenType() == IDEN && !errorDetected)
    {
        theFunc = new ASTFunction(scan->currentTokenString(),typeList);
        scan->advance();
    }
    else if (!errorDetected)
    {
        printError("E2b", "Expecting IDEN after return type", scan->getLine());
    }

    //LPAREN
    if (scan->currentTokenType() == LPAREN && !errorDetected)
    {
        scan->advance();
    }
    else if (!errorDetected)
    {
        printError("E3", "Expecting ( after IDEN", scan->getLine());
    }

    //optional list of params | IDEN
    if (scan->currentTokenType() == IDEN && !errorDetected)
    {
        theFunc->addParams(rdpParam());
    }

    //RPAREN
    if (scan->currentTokenType() == RPAREN && !errorDetected)
    {
        scan->advance();
    }
    else if (!errorDetected)
    {
        printError("E4", "Expecting ) to close parameters", scan->getLine());
    }

    //LBRACE
    if (scan->currentTokenType() == LBRACE && !errorDetected)
    {
        scan->advance();
    }
    else if (!errorDetected)
    {
        printError("E5", "Expecting { ", scan->getLine());
    }

    //STATEMENTS
    if ((scan->currentTokenType() == IDEN || scan->currentTokenType() == LBRACE || scan->currentTokenType() == COMMA) && !errorDetected)
    {
        theFunc -> addStmts(rdpStatements()); //ADD A STATEMENTS OBJ TO THE FUNCTION OBJ
    }
    else if (!errorDetected)
    {
        printError("E2b", "Expecting IDEN after return type (Stmts in Func)", scan->getLine());
    }

    //RBRACE
    if (scan->currentTokenType() == RBRACE && !errorDetected)
    {
        scan->advance();
    }
    else if (!errorDetected)
    {
        printError("E6", "Expecting } ", scan->getLine());
    }

    return theFunc;
}

// ** rdpParam code compliments of Dr. Benjamin Mood of Point Loma Nazarene University **
ASTParam* Parser::rdpParam()
{
    ASTParam* param = new ASTParam();

    string type;
    string name;

    //IDEN
    if (scan->currentTokenType() == IDEN && !errorDetected)
    {
        type = scan->currentTokenString();
        scan->advance();
    }
    else if(!errorDetected)
    {
        printError("E7", "Expecting IDEN for function parameter type ", scan->getLine());
    }

    //IDEN
    if (scan->currentTokenType() == IDEN && !errorDetected)
    {
        name = scan->currentTokenString();
        scan->advance();
    }
    else if (!errorDetected)
    {
        printError("E8", "Expecting IDEN for function parameter name ", scan->getLine());
    }
    param->addParam(name, type);

    //WHILE COMMA, KEEP ADDING PARAMS
    while (scan->currentTokenType() == COMMA && !errorDetected)
    {
        scan->advance();

        if (scan->currentTokenType() == IDEN && !errorDetected)
        {
            type = scan->currentTokenString();
            scan->advance();
        }
        else if (!errorDetected)
        {
            printError("E7", "Expecting IDEN for function parameter type ", scan->getLine());
        }

        if (scan->currentTokenType() == IDEN && !errorDetected)
        {
            name = scan->currentTokenString();
            scan->advance();
        }
        else if (!errorDetected)
        {
            printError("E8", "Expecting IDEN for function parameter name ", scan->getLine());
        }
        param->addParam(name, type);
    }

    return param;
}

ASTNode * Parser::rdpTypeList() {
    vector<string> types;

    //IDEN
    if (scan->currentTokenType() == IDEN && !errorDetected)
    {
        types.push_back(scan->currentTokenString());
        scan->advance();
    }
    else if (!errorDetected)
    {
        printError("E9", "Expecting IDEN for function parameter type ", scan->getLine());
    }

    //WHILE COMMA, KEEP TAKING IN RETURN TYPES
    while(scan->currentTokenType() == COMMA && !errorDetected) {
        scan->advance();

        if(scan->currentTokenType() == IDEN && !errorDetected) {
            types.push_back(scan->currentTokenString());
            scan -> advance();
        } else if(!errorDetected) {
            printError("E10: ", "Expecting IDEN after COMMA in return type ", scan->getLine());
        }
    }

    return new ASTTypeList(types);

}

ASTStatements * Parser::rdpStatements() {
    ASTStatements * stmts = new ASTStatements();

    //WHILE IT IS AN IDEN, LBRACE, OR COMMA, ADD A STATEMENT EACH TIME THROUGH
    while((scan->currentTokenType() == IDEN || scan->currentTokenType() == LBRACE || scan->currentTokenType() == COMMA)&& !errorDetected){
        stmts -> addStmt( rdpStatement());
        cout << "in statements, current token is: " << scan->currentTokenString() << "\n";
    }

    return stmts;
}

ASTstatement * Parser::rdpStatement() {
    string idenName = scan -> currentTokenString();
    ASTstatement * statement = NULL;
    string type;

    //DETERMINE TYPE OF STATEMENT IT IS, AND ADD THAT TO STATEMENT OBJ
    if(scan -> currentTokenType() == IDEN && !errorDetected) {
        if (scan->currentTokenString() == "if" && !errorDetected)   //IF
        {
            type = "if";
            statement = new ASTstatement(idenName, type);
            statement -> addIf(rdpIf());
        } else if (scan->currentTokenString() == "for" && !errorDetected) { //FOR
            type = "for";
            statement = new ASTstatement(idenName, type);
            statement -> addFor(rdpFor());
        }
        else if(scan->currentTokenString() == "return" && !errorDetected) { //RETURN
            type = "return";
            statement = new ASTstatement(idenName, type);
            statement -> addReturn(rdpReturn());
        }
        //CHECK THOSE THAT START WITH AN UNSPECIFIC IDEN AND CHECK NEXT TOKEN TO DETERMINE STATEMENT TYPE
        else if(scan -> currentTokenType() == IDEN && !errorDetected) {
            scan -> advance();
            cout << "made it into statement IDEN\n";

            if(scan -> currentTokenType() == IDEN && !errorDetected) {  //DECLARATION
                type = "declaration";
                statement = new ASTstatement(idenName, type);

                ASTdeclaration * declaration = rdpDeclaration(true);
                declaration->addIden(idenName); //first IDEN
                declaration->addIden(scan->currentTokenString()); //second IDEN
                statement -> addDeclaration(declaration);
            } else if (scan -> currentTokenType() == EQL && !errorDetected) {   //ASSIGN
                type = "assign";
                statement = new ASTstatement(idenName, type);

                ASTassign * assign = rdpAssign(true);
                assign -> addIden(idenName);
                statement -> addAssign(assign);
            } else if (scan -> currentTokenType() == LPAREN && !errorDetected) { //FUNCTION CALL (I READ IT WRONG THE FIRST TIME SO ITS REFERRED TO AS FUNCTIONAL1 THROUGHOUT, SORRY)
                type = "functionCall";
                statement = new ASTstatement(idenName, type);

                ASTfunctionCall * functionCall = rdpFunctionCall();
                functionCall -> addIden(idenName);
                statement -> addFunctionCall(functionCall);

                //RPAREN
                if(scan->currentTokenType() == RPAREN) {
                    scan->advance();
                }

                //EOL
                if (scan->currentTokenType() == EOL && !errorDetected)
                {
                    scan->advance();
                }
                else if (!errorDetected)
                {
                    printError("E6", "Expecting EOL statement ", scan->getLine());
                }

            } else if (!errorDetected) {
                printError("E7", "Expecting IDEN for function parameter type statement iden", scan->getLine());
            }
        }
    } else if(scan -> currentTokenType() == COMMA && !errorDetected) {  //FUNCTION-CALL-MULTIPLE-RETURN
        type = "multipleReturn";
        statement = new ASTstatement(idenName, type);
        ASTmultipleReturn * mr = rdpMultipleReturn();
        mr->addIden("return");
        statement -> addMultipleReturn(mr);
    } else if(scan -> currentTokenType() == LBRACE && !errorDetected) { //BLOCK-STATEMENT
        type = "block";
        statement = new ASTstatement(idenName, type);
        statement -> addBlockStatement(rdpBlockStatement());
    } else {
        printError("E14", "Expecting IDEN/COMMA/LBRACE for statement", scan->getLine());
    }

    return statement;
}

ASTargs * Parser::rdpArgs() {
    ASTargs * args = new ASTargs();

    //IDEN OR CONSTANT
    if ((scan->currentTokenType() == IDEN || scan->currentTokenType() == CONSTANT)&& !errorDetected)
    {
        args->addBoolA(rdpBooleanExprA());
    }
    else if (!errorDetected)
    {
        printError("E6", "Expecting IDEN in Args 1 ", scan->getLine());
    }

    //WHILE THERE ARE STILL COMMAS, KEEP READING IN BOOLEAN EXPRESSIONS
    while (scan->currentTokenType() == COMMA && !errorDetected)
    {
        scan->advance();

        if ((scan->currentTokenType() == IDEN || scan->currentTokenType() == CONSTANT) && !errorDetected)
        {
            args->addBoolA(rdpBooleanExprA()); //ADD BOOLEAN A
        }
        else if (!errorDetected)
        {
            printError("E6", "Expecting IDEN in Args 2 ", scan->getLine());
        }
    }

    return args;
}

ASTif * Parser::rdpIf() {
    ASTif * theIf = new ASTif();

    //ENSURE AGAIN THAT ITS AN IF
    if (scan->currentTokenString() == "if" && !errorDetected)
    {
        scan->advance();
    }
    else if(!errorDetected)
    {
        printError("E7", "Expecting IDEN for function if type ", scan->getLine());
    }

    //LPAREN
    if (scan->currentTokenType() == LPAREN && !errorDetected)
    {
        scan->advance();
    }
    else if (!errorDetected)
    {
        printError("E6", "Expecting ( ", scan->getLine());
    }

    //ADD BOOL A OBJ TO IF OBJ
    if ((scan->currentTokenType() == IDEN || scan->currentTokenType() == CONSTANT) && !errorDetected)
    {
        theIf->addBoolA(rdpBooleanExprA());

    }
    else if (!errorDetected)
    {
        printError("E6", "Expecting IDEN or CONSTANT", scan->getLine());
    }

    //RPAREN
    if (scan->currentTokenType() == RPAREN && !errorDetected)
    {
        scan->advance();
    }
    else if (!errorDetected)
    {
        printError("E6", "Expecting ) ", scan->getLine());
    }

    //STATEMENT
    if((scan->currentTokenType() == IDEN || scan->currentTokenType() == COMMA || scan->currentTokenType() == LBRACE) && !errorDetected){
        theIf->addStatement(rdpStatement());
        cout << "made it into if statement\n";
    } else if (!errorDetected)
    {
        printError("E12", "Expecting IDEN/COMMA/LPAREN ", scan->getLine());
    }

    return theIf;
}

ASTfor * Parser::rdpFor() {
    ASTfor * theFor = new ASTfor();

    //IDEN
    if (scan->currentTokenType() == IDEN && !errorDetected)
    {
        scan->advance();
    }
    else if(!errorDetected)
    {
        printError("E7", "Expecting IDEN for function for type ", scan->getLine());
    }

    //LPAREN
    if (scan->currentTokenType() == LPAREN && !errorDetected)
    {
        scan->advance();
    }
    else if (!errorDetected)
    {
        printError("E6", "Expecting ( ", scan->getLine());
    }

    //ADD DECLARATION OBJ TO FOR OBJ
    if (scan->currentTokenType() == IDEN && !errorDetected)
    {
        theFor->addDeclaration(rdpDeclaration(false));
    }
    else if (!errorDetected)
    {
        printError("E6", "Expecting IDEN ", scan->getLine());
    }

    //ADD BOOL A TO FOR OBJ
    if ((scan->currentTokenType() == IDEN || scan->currentTokenType() == CONSTANT) && !errorDetected)
    {
        theFor->addBoolA(rdpBooleanExprA());
    }
    else if (!errorDetected)
    {
        printError("E6", "Expecting IDEN ", scan->getLine());
    }

    //EOL
    if (scan->currentTokenType() == EOL && !errorDetected)
    {
        scan->advance();
    }
    else if (!errorDetected)
    {
        printError("E6", "Expecting EOL after bool", scan->getLine());
    }

    //ADD ASSIGN OBJ TO FOR OBJ
    if((scan->currentTokenType() == IDEN && scan->nextTokenType()) && !errorDetected){
        theFor->addAssign(rdpAssign(false));
    } else if (!errorDetected){
        printError("E12", "Expecting IDEN ", scan->getLine());
    }

    //RPAREN
    if (scan->currentTokenType() == RPAREN && !errorDetected)
    {
        scan->advance();
    }
    else if (!errorDetected)
    {
        printError("E6", "Expecting ) ", scan->getLine());
    }

    //ADD STATEMENT TO FOR OBJ
    if((scan->currentTokenType() == IDEN || scan->currentTokenType() == COMMA || scan->currentTokenType() == LBRACE) && !errorDetected){
        theFor->addStatement((ASTstatement *) rdpStatement());
    } else if (!errorDetected) {
        printError("E13", "Expecting a statement (IDEN/COMMA/LPAREN) ", scan->getLine());
    }

    return theFor;
}

ASTreturn * Parser::rdpReturn() {
    ASTreturn * theReturn = new ASTreturn();

    //IDEN
    if (scan->currentTokenType() == IDEN && !errorDetected)
    {
        scan->advance();
    }
    else if(!errorDetected)
    {
        printError("E7", "Expecting IDEN for function for return ", scan->getLine());
    }

    //IF THERES A BOOLEAN A, ADD IT. IF NOT, SKIP
    if((scan->currentTokenType() == IDEN || scan->currentTokenType() == CONSTANT) && !errorDetected) {
        theReturn->addBoolA(rdpBooleanExprA());

        //CAN HAVE MULTIPLE CBOOLEAN EXPRESSIONS HERE, SO KEEP ADDING AS LONG AS THERE ARE STILL COMMAS
        while(scan->currentTokenType() == COMMA && !errorDetected) {
            scan->advance();
            if((scan->currentTokenType() == IDEN || scan->currentTokenType() == CONSTANT) && !errorDetected) {
                theReturn->addBoolA(rdpBooleanExprA());
            }
            else {
                printError("E7", "Expecting IDEN or CONST for function for return's optional comma-boola ", scan->getLine());
            }
        }
    }

    //EOL
    if (scan->currentTokenType() == EOL && !errorDetected)
    {
        scan->advance();
    }
    else if (!errorDetected)
    {
        printError("E6", "Expecting EOL return", scan->getLine());
    }

    return theReturn;
}

ASTdeclaration * Parser::rdpDeclaration(bool firstIdenScannedAlready) {
    ASTdeclaration * declaration = new ASTdeclaration();

    //CHECK TO SEE IF DEC IS BEING CALLED FROM A PLACE THAT ALREADY READ IN THE FIRST IDEN OR NOT. IF NOT, READ IT IN
    if(!firstIdenScannedAlready) {
        if (scan->currentTokenType() == IDEN && !errorDetected)
        {
            declaration->addIden(scan->currentTokenString());
            cout << "first iden in dec: " << scan->currentTokenString() << "\n";
            scan->advance();
        }
        else if (!errorDetected)
        {
            printError("E6", "Expecting IDEN ", scan->getLine());
        }
    }

    //IDEN 2
    if (scan->currentTokenType() == IDEN && !errorDetected)
    {
        declaration->addIden(scan->currentTokenString());
        cout << "second iden in dec: " << scan->currentTokenString() << "\n";

        scan->advance();
    }
    else if (!errorDetected)
    {
        printError("E6", "Expecting IDEN ", scan->getLine());
    }

    // IF THERE IS AN =, READ IN AND ADD BOOL A OBJ TO DECLARATION OBJ
    if (scan->currentTokenType() == EQL && !errorDetected)
    {
        scan->advance();

        if ((scan->currentTokenType() == IDEN || scan->currentTokenType() == CONSTANT)&& !errorDetected) {
            ASTbooleanExprA  *boolA = rdpBooleanExprA();
            declaration->adjustOptions(true);
            declaration->addBoolExprA(boolA);
        } else {
            printError("E6", "Expecting IDEN in declaration boolA", scan->getLine());
        }
    }

    //EOL
    if (scan->currentTokenType() == EOL && !errorDetected)
    {
        scan->advance();
    }
    else if (!errorDetected)
    {
        printError("E6", "Expecting EOL declaration", scan->getLine());
    }

    return declaration;
}

ASTassign * Parser::rdpAssign(bool firstIdenAlreadyScanned) {
    ASTassign * assign = new ASTassign();

    //CHECK TO SEE IF DEC IS BEING CALLED FROM A PLACE THAT ALREADY READ IN THE FIRST IDEN OR NOT. IF NOT, READ IT IN
    if(!firstIdenAlreadyScanned) {
        if (scan->currentTokenType() == IDEN && !errorDetected)
        {
            assign->addIden(scan->currentTokenString());
            scan->advance();
        }
        else if (!errorDetected)
        {
            printError("E6", "Expecting IDEN in assign", scan->getLine());
        }
    }

    //EQL
    if (scan->currentTokenType() == EQL && !errorDetected)
    {
        scan->advance();
    }
    else if (!errorDetected)
    {
        printError("E6", "Expecting EQL ", scan->getLine());
    }

    //ADD BOOL A OBJ TO ASSIGN OBJ
    if ((scan->currentTokenType() == IDEN || scan->currentTokenType() == CONSTANT) && !errorDetected)
    {
        assign->addBoolExprA(rdpBooleanExprA());
    }
    else if (!errorDetected)
    {
        printError("E6", "Expecting IDEN for bool exp A in assign ", scan->getLine());
    }

    //EOL
    if (scan->currentTokenType() == EOL && !errorDetected)
    {
        scan->advance();
    }
    else if (!errorDetected)
    {
        printError("E6", "Expecting EOL in assign", scan->getLine());
    }

    return assign;
}

ASTfunctionCall * Parser::rdpFunctionCall() {
    ASTfunctionCall * functionCall = new ASTfunctionCall();

    //LPAREN
    if (scan->currentTokenType() == LPAREN && !errorDetected)
    {
        scan->advance();
    }
    else if (!errorDetected)
    {
        printError("E6", "Expecting ( ", scan->getLine());
    }

    // 0,1 ARGS
    if(scan->currentTokenType() == IDEN && !errorDetected) {
        functionCall->addArgs(rdpArgs());
    }

    //RPAREN
    if (scan->currentTokenType() == RPAREN && !errorDetected)
    {
        scan->advance();
    }
    else if (!errorDetected)
    {
        printError("E6", "Expecting ) ", scan->getLine());
    }

    return functionCall;
}

ASTmultipleReturn *Parser::rdpMultipleReturn() {
    ASTmultipleReturn * multipleReturn = new ASTmultipleReturn();

    //IDEN
    if (scan->currentTokenType() == IDEN && !errorDetected)
    {
        multipleReturn->addIden(scan->currentTokenString());
    }
    else if (!errorDetected)
    {
        printError("E6", "Expecting IDEN ", scan->getLine());
    }

    //WHILE THERE ARE COMMAS, CONTINUE TO ADD IDENS THAT MAKE UP THE RETURN STATEMENT
    while(scan->currentTokenType() == COMMA && !errorDetected) {
        scan->advance();

        if (scan->currentTokenType() == IDEN && !errorDetected)
        {
            multipleReturn->addIden(scan->currentTokenString());
        }
        else if (!errorDetected)
        {
            printError("E6", "Expecting IDEN ", scan->getLine());
        }
    }

    //EQL
    if (scan->currentTokenType() == EQL && !errorDetected)
    {
        scan->advance();
    }
    else if (!errorDetected)
    {
        printError("E6", "Expecting EQL ", scan->getLine());
    }

    //LPAREN
    if (scan->currentTokenType() == LPAREN && !errorDetected)
    {
        multipleReturn->addFunctionCall(rdpFunctionCall());
    }
    else if (!errorDetected)
    {
        printError("E6", "Expecting LPAREN/functionCall ", scan->getLine());
    }

    //EOL
    if (scan->currentTokenType() == EOL && !errorDetected)
    {
        scan->advance();
    }
    else if (!errorDetected)
    {
        printError("E6", "Expecting EOL multiple return ", scan->getLine());
    }

    return multipleReturn;
}

ASTblockStatement *Parser::rdpBlockStatement() {
    ASTblockStatement * block = new ASTblockStatement();

    //LBRACE
    if (scan->currentTokenType() == LBRACE && !errorDetected)
    {
        scan->advance();
    }
    else if (!errorDetected)
    {
        printError("E6", "Expecting {LBRACE} ", scan->getLine());
    }

    //ADD STATEMENTS OBJ TO BLOCK STATEMENT OBJ
    if ((scan->currentTokenType() == LBRACE || scan->currentTokenType() == COMMA ||scan->currentTokenType() == IDEN) && !errorDetected) {
        ASTStatements * statements = rdpStatements();

        if (scan->currentTokenType() == IDEN) {
            statements->addIden(scan->currentTokenString());
        }

        block -> addStatements(statements);
    }
    else if (!errorDetected)
    {
        printError("E6", "Expecting LBRACE|COMMA|IDEN ", scan->getLine());
    }

    //RBRACE
    if (scan->currentTokenType() == RBRACE && !errorDetected)
    {
        scan->advance();
    }
    else if (!errorDetected)
    {
        printError("E6", "Expecting } ", scan->getLine());
    }

    return block;
}

ASTbooleanExprA * Parser::rdpBooleanExprA() {
    ASTbooleanExprA * boolA = new ASTbooleanExprA();

    //ADD BOOL B OBJ TO BOOL A OBJ
    if ((scan->currentTokenType() == IDEN || scan->currentTokenType() == CONSTANT) && !errorDetected)
    {
        boolA->addBoolExprB(rdpBooleanExprB());
    }
    else if (!errorDetected)
    {
        printError("E12", "Expecting IDEN (bool exp B in bool exp A)", scan->getLine());
    }

    //WHILE THERE ARE & | OPERATORS AND MORE BOOL EXPRS, ADD THEM
    while ((scan->currentTokenType() == AND || scan->currentTokenType() == OR) && !errorDetected) {
        boolA->addOperator(scan->currentTokenString());
        scan->advance();

        // BOOL B
        if ((scan->currentTokenType() == IDEN || scan->currentTokenType() == CONSTANT) && !errorDetected) {
            boolA->addBoolExprB(rdpBooleanExprB());
        } else if (!errorDetected) {
            printError("E12", "Expecting IDEN (bool exp B in bool exp A)", scan->getLine());
        }
    }

    return boolA;
}

ASTbooleanExprB * Parser::rdpBooleanExprB(){
    ASTbooleanExprB * boolB = new ASTbooleanExprB();

    //TERM
    if((scan->currentTokenType() == IDEN || scan->currentTokenType() == CONSTANT) && !errorDetected) {
        boolB->addTerm(rdpTerm());
    } else {
        printError("E12", "Expecting IDEN (term1 in bool exp B)", scan->getLine());

    }

    //WHILE THERE ARE STILL OPERATORS AND BOOL BS, ADD THEM
    while ((scan->currentTokenType() == EE || scan->currentTokenType() == GR || scan->currentTokenType() == GRE) && !errorDetected)
    {
        boolB -> addOperator(scan->currentTokenString());
        scan->advance();
        if((scan->currentTokenType() == IDEN || scan->currentTokenType() == CONSTANT) && !errorDetected){
            boolB->addTerm(rdpTerm());
        } else {
            printError("E12", "Expecting IDEN (term2+ in bool exp B)", scan->getLine());
        }
    }

    return boolB;
}

ASTterm * Parser::rdpTerm() {
    ASTterm * term = new ASTterm();

    //EXPR
    if ((scan->currentTokenType() == IDEN || scan->currentTokenType() == CONSTANT)&& !errorDetected)
    {
        term->addExpr(rdpExpr());
    }
    else if (!errorDetected)
    {
        printError("E12", "Expecting IDEN (expr 1 in term", scan->getLine());
    }

    //WHILE THERE ARE STILL + - OPERATORS AND EXPRS, ADD THEM
    while ((scan->currentTokenType() == PLUS || scan->currentTokenType() == MINUS) && !errorDetected) {
        term->addOperator(scan->currentTokenString());
        scan->advance();

        // EXPR
        if ((scan->currentTokenType() == IDEN || scan->currentTokenType() == CONSTANT) && !errorDetected) {
            term->addExpr(rdpExpr());
        } else if (!errorDetected) {
            printError("E12", "Expecting IDEN (expr 2 in term", scan->getLine());
        }
    }

    return term;
}

ASTexpr * Parser::rdpExpr() {
    ASTexpr * expr = new ASTexpr();

    //POW
    if ((scan->currentTokenType() == IDEN || scan->currentTokenType() == CONSTANT) && !errorDetected)
    {
        expr->addPow(rdpPow());
    }
    else if (!errorDetected)
    {
        printError("E12", "Expecting IDEN (pow 1 in expr", scan->getLine());
    }

    //WHILE THERE ARE * / OPERATORS AND POWS, ADD THEM
    while ((scan->currentTokenType() == MULTIPLY || scan->currentTokenType() == DIVIDE) && !errorDetected) {
        expr->addOperator(scan->currentTokenString());
        scan->advance();

        //POW
        if ((scan->currentTokenType() == IDEN || scan->currentTokenType() == CONSTANT) && !errorDetected) {
            expr->addPow(rdpPow());
        } else if (!errorDetected) {
            printError("E12", "Expecting IDEN (pow 2 in expr", scan->getLine());
        }
    }

    return expr;
}

ASTpow * Parser::rdpPow() {
    ASTpow * pow = new ASTpow();

    //FACTOR
    if ((scan->currentTokenType() == IDEN || scan->currentTokenType() == CONSTANT) && !errorDetected)
    {
        pow->addFactor(rdpFactor());
    }
    else if (!errorDetected)
    {
        printError("E12", "Expecting IDEN (factor 1 in pow", scan->getLine());
    }

    //WHILE THERE ARE POW OPERATORS AND FACTORS, ADD THEM
    while (scan->currentTokenType() == POW  && !errorDetected) {
        scan->advance();

        //FACTOR
        if ((scan->currentTokenType() == IDEN || scan->currentTokenType() == CONSTANT) && !errorDetected) {
            pow->addFactor(rdpFactor());
        } else if (!errorDetected) {
            printError("E12", "Expecting IDEN (factor 2 in pow", scan->getLine());
        }
    }

    return pow;
}

ASTfactor * Parser::rdpFactor() {
    ASTfactor * factor = new ASTfactor();

    //IF ITS AN ELEMENT, TREAT IT AS SUCH, IF ITS OTHER OPTION, TREAT IT AS SUCH
    if((scan->currentTokenType() == IDEN || scan->currentTokenType() == CONSTANT)) { //ELEMENT
        factor ->addElement(rdpElement());
    } else if (scan->currentTokenType() == LPAREN) { //OTHER OPTION
        scan->advance();

        if ((scan->currentTokenType() == IDEN || scan->currentTokenType() == CONSTANT) && !errorDetected) {
            factor->addBoolA(rdpBooleanExprA());
        } else if (!errorDetected) {
            printError("E12", "Expecting IDEN (boolA in factor", scan->getLine());
        }

        if (scan->currentTokenType() == RPAREN && !errorDetected) {
            scan->advance();
        } else if (!errorDetected) {
            printError("E6", "Expecting RPAREN (factor)", scan->getLine());
        }
    } else {
        printError("E13", "Expecting IDEN or LPAREN in factor", scan->getLine());
    }

    return factor;
}

ASTelement * Parser::rdpElement() {
    ASTelement * element = new ASTelement();
    string idenName = "";

    //IF ITS AN IDEN TREAT IT AS SUCH
    if(scan->currentTokenType() == IDEN && !errorDetected) {
        idenName = scan->currentTokenString();
        scan->advance();

        //ADD FUNCTION CALL
        if((idenName != "if" && idenName != "for") && scan->currentTokenType() == LPAREN) {
            element->addFunctionCall(rdpFunctionCall());
            element->addType("functionCall");
        } else {     //ADD IDEN
            element->addIden(idenName);
            element->addType("iden");
        }
    } else if (scan->currentTokenType() == CONSTANT && !errorDetected) { //ADD CONSTANT
        element->addConst(stoi(scan->currentTokenString()));
        element->addType("constant");
        scan->advance();
    }

    return element;
}