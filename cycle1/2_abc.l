%{
	#include<stdio.h>
%}
%option noyywrap
%%
"abc" {yytext="ABC"; ECHO;}
. {ECHO;}
%%
int main(){
	printf("Enter some input text: ");
	yylex();
	return 0;
}
