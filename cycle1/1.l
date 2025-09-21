%{
	#include<stdio.h>
	int dig_count=0;
%}
%option noyywrap
%%
[0-9] {dig_count++;}
\n {return 0;}
. ;
%%

int main(){
	yylex();
	printf("Count=%d\n",dig_count);
	return 0;
}
