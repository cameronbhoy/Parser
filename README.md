# Parser
This was a project given in my Programming Languages class at Point Loma Nazarene University.  Throughout the duration of the class, spanned across many projects, we built a compiler for a language that was created for said class.  As such, this project focuses on making the parser component of a compiler work.  Most of my work can be found in Parser.h, Parser.cpp, AST.h, and AST.cpp.  That which was given to us by our professor, Dr. Benjamin Mood, is denoted by comments found in the code.

This program takes in an unformatted piece of the class's code and parses it.  It prints out the code to ensure everything was read in correctly.


The language's syntax, in EBNF, is as follows:

\<program\> := \<function\> { \<function\> }  

\<function\> := \<typelist\> IDEN LPAREN [\<param\>] RPAREN LBRACE \<statements\> RBRACE 

\<typelist\> := IDEN {COMMA IDEN }

\<param\> := IDEN IDEN { COMMA IDEN IDEN} 

\<statements\> := { \<statement\> } 

\<statement\> := \<if\> | \<for\> | \<declaration\> | \<assign\> | \<blockstatement\> | \<functioncall\> EOL | \<return\> | \<functioncallstatementmultipleretrun\>

\<args\> := \<booleanExprA\> {COMMA \<booleanExprA\>}



\<for\> := IDEN (where IDEN = for) LPAREN \<declaration\> \<booleanEXPRA\> EOL \<assign\> RPAREN \<statement\>

\<if\> := IDEN (where IDEN = if) LPAREN \<booleanEXPRA\> RPAREN \<statement\>

\<assign\> := IDEN EQL \<booleanExprA\> EOL

\<return\> := IDEN (where IDEN = return) [\<booleanExprA\> {COMMA \<booleanExprA\>}] EOL

\<functioncall\> := IDEN LPAREN [\<args\>] RPAREN

\<blockstatement\> := LBRACE \<statements\> RBRACE

\<declaration\> := IDEN IDEN [EQL \<booleanExprA\>] EOL

\<functioncallstatementmultipleretrun\> := COMMA IDEN {COMMA IDEN} EQL  \<functioncall\> EOL



\<booleanExprA\> := \<booleanExprB\> {(AND | OR) \<booleanExprB\>}

\<booleanExprB\> := \<term\> {(EE | GR | GRE) \<term\>}

\<term\> := \<expr\> { ( PLUS | MINUS ) \<expr\>} 

\<expr\> := \<pow\> { ( MULTIPLY  | DIVIDE ) \<pow\>}  

\<pow\> := \<factor\> { POW  \<factor\>}  

\<factor\> := \<element\> | LPAREN  \<booleanExprA\> RPAREN

\<element\> := IDEN | CONST | \<functioncall\>
