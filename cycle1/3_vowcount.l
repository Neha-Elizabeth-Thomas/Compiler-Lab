%{
#include<stdio.h>
int vow=0,con=0;
%}
%option noyywrap

%%
[aeiouAEIOU] {vow++;}
[a-zA-Z] {con++;}
.
%%
void main(){
	printf("Enter a string: ");
	yylex();
	printf("Vowel count=%d\n",vow);
	printf("Cosnsonalt count=%d\n",con);
}
