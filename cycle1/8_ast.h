#include<stdio.h>

typedef struct astnode{
	int val;	
	struct astnode* left;
	struct astnode* right;
	char op;
}astnode;
astnode* makenode(char op,astnode* left,astnode* right);
astnode* makeleaf(int val);
void printast(astnode* node);
