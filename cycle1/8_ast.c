#include "8_ast.h"
#include<stdlib.h>

astnode* makenode(char op,astnode* left,astnode* right){
	astnode* node=(astnode*)malloc(sizeof(astnode));
	node->op=op;
	node->left=left;
	node->right=right;
	node->val=0;
	return node;
}

astnode* makeleaf(int val){
	astnode* leaf=(astnode*)malloc(sizeof(astnode));
	leaf->val=val;
	leaf->op=0;
	leaf->left=NULL;
	leaf->right=NULL;
	return leaf;
}

void printast(astnode* node){
	if(node->left){
		printast(node->left);
	}
	if(node->right){
		printast(node->right);
	}
	if(node->op){
		printf("%c",node->op);
	}else{
		printf("%d",node->val);
	}
}
