%{
int yylex();
int yyerror();
#include<stdio.h>
#define YYSTYPE double
%}
%token num

%left '+' '-'
%left '*' '/'
%left '(' ')'
%%
start	:E '\n' {printf("=%f\n",$1); return num;}
E	:E '+' E {$$=$1+$3;}
	|E '-' E {$$=$1-$3;}
	|E '*' E {$$=$1*$3;}
	|E '/' E {$$=$1/$3;}
	|'(' E ')' {$$=$2;}
	|num {$$=$1;}
	;
	
%%
int main(){
	return yyparse();
}

int yyerror(){
	printf("Invalid Expression\n");
}
