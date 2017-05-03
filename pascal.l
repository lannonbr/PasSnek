%{
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "tree.h"
#include "util.h"
#include "statement.h"
#include "pascal.tab.h"
%}

%%

"(*".*"*)" {}
"{".*"}" {}
"program" { return PROGRAM; }
"array" { return ARRAY; }
"var" { return VAR; }
"of" { return OF; }
"integer" { return INTEGER; }
"real" { return REAL; }
"function" { return FUNCTION; }
"procedure" { return PROCEDURE; }
"begin" { return BBEGIN; }
"end" { return END; }
":=" { return ASSIGNOP; }
"if" { return IF; }
"then" { return THEN; }
"else" { return ELSE; }
"while" { return WHILE; }
"do" { return DO; }
"<" { yylval.bopval = 0; return RELOP; }
"<=" { yylval.bopval = 1; return RELOP; }
">" { yylval.bopval = 2; return RELOP; }
">=" { yylval.bopval = 3; return RELOP; }
"=" { yylval.bopval = 4; return RELOP; }
"<>" { yylval.bopval = 5; return RELOP; }
"+" { yylval.bopval = 6; return ADDOP; }
"-" { yylval.bopval = 7; return ADDOP; }
"or" { yylval.bopval = 8; return ADDOP; }
"*" { yylval.bopval = 9; return MULOP; }
"/" { yylval.bopval = 10; return MULOP; }
"%" { yylval.bopval = 11; return MULOP; }
"and" { yylval.bopval = 12; return MULOP; }
"not" { return NOT; }
"." { return '.'; }
"," { return ','; }
".." { return DOTDOT; }
":" { return ':'; }
";" { return ';'; }
"(" { return '('; }
")" { return ')'; }
"[" { return '['; }
"]" { return ']'; }
[A-Za-z][A-Za-z0-9]* { yylval.sval = strdup(yytext); return IDENT; }
[0-9]+ { yylval.ival = atoi(yytext); return INUM; }
[0-9]+\.[0-9]+ { yylval.fval = atof(yytext); return RNUM; }
[ \t] {}
[\n] {}
. { fprintf(stderr, "Unkown token: %s", yytext); }

%%
