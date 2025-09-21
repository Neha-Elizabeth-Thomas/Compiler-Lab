%{
#include "8_ast.h"
#include "y.tab.h"
%}
%option noyywrap
%%
[0-9]+ {yylval.INT=atoi(yytext); return num;}
\n {return '\n';}
. {return yytext[0];}
%%
