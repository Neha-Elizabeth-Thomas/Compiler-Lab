%{
#include<stdio.h>
int lines=0,words=0,chars=0;
%}
%option noyywrap
%%
"\n" {lines++; chars++;}
[^\t\n ]+ {words++; chars+=yyleng;}
. {chars++;}
%%
void main(int argc,char** argv){
	yyin=fopen(argv[1],"r");
	yylex();
	printf("lines=%d\nchars=%d\nwords=%d\n",lines,chars,words);
	fclose(yyin);
}
