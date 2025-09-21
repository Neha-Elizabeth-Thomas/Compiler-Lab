%{
#include "8_ast.h"
int yylex();
int yyerror(char* msg);
astnode* root=NULL;
%}
%union{
	int INT;
	astnode* ptr;
}
%token <INT> num;

%left '+' '-'
%left '*' '/'
%left '(' ')'
%%
start	:E '\n' {root=$<ptr>1; return 0;}
E	:E '+' E {$<ptr>$=makenode('+',$<ptr>1,$<ptr>3);}
	|E '-' E {$<ptr>$=makenode('-',$<ptr>1,$<ptr>3);}
	|E '*' E {$<ptr>$=makenode('*',$<ptr>1,$<ptr>3);}
	|E '/' E {$<ptr>$=makenode('/',$<ptr>1,$<ptr>3);}
	|'(' E ')' {$<ptr>$=$<ptr>2;}
	|num {$<ptr>$=makeleaf($<INT>1);}
	;
%%
int main(){
	printf("Enter an arithmetic expression: ");
	yyparse();
	printast(root);
	printf("\n");
	return 0;
}

int yyerror(char* msg){
	fprintf(stderr,"%s",msg);
	return 0;
}
