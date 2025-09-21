#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define OPNDSIZE 10
#define MAXQUADS 20


void fold();
void propagate();

struct quadruple{
	char op;
	char op1[OPNDSIZE];
	char op2[OPNDSIZE];
	char res[OPNDSIZE];
};
struct quadruple quads[MAXQUADS];
int numquads;


int isint(char opnd[]){
	for(int i=0 ; opnd[i]!='\0' ; i++){
		if(!isdigit(opnd[i]))
			return 0;
	}
	return 1;
}

int calculate(int i){
	int res;
	switch(quads[i].op){
		case '+':res=atoi(quads[i].op1)+atoi(quads[i].op2);
			break;
		case '-':res=atoi(quads[i].op1)-atoi(quads[i].op2);
			break;
		case '*':res=atoi(quads[i].op1)*atoi(quads[i].op2);
			break;
		case '/':res=atoi(quads[i].op1)/atoi(quads[i].op2);
			break;
	}
	return res;
}

char* getconstval(char opnd[]){
	for(int i=0 ; i<numquads ; i++){
		if(quads[i].op=='=' && strcmp(quads[i].res,opnd)==0)
			return quads[i].op1;
	}
	return opnd;
}

void fold(){
	int changed=0;
	for(int i=0 ; i<numquads ; i++){
		if(isint(quads[i].op1) && isint(quads[i].op2)){
			int res=calculate(i);
			quads[i].op='=';
			sprintf(quads[i].op1,"%d",res);
			strcpy(quads[i].op2,"-");
			changed=1;
		}
	}
	if(changed){
		propagate();
	}
}

void propagate(){
	for(int i=0 ; i<numquads ; i++){
		strcpy(quads[i].op1,getconstval(quads[i].op1));
		strcpy(quads[i].op2,getconstval(quads[i].op2));
		if(isint(quads[i].op1) && isint(quads[i].op2)){
			fold();
		}

	}
}

void main(){
	printf("How many quadruples? ");
	scanf("%d",&numquads);

	printf("Enter %d quadruples: \n",numquads);
	for(int i=0 ; i<numquads ; i++){
		scanf(" %c %s %s %s",&quads[i].op,quads[i].op1,quads[i].op2,quads[i].res);
	}

	fold();
	
	printf("After CONSTANT FOLDING AND PROPAGATION\n");
	printf("Operator|Operand1|Operand2|Result\n");
	for(int i=0 ; i<numquads ; i++){
		printf("%-8c|%-8s|%-8s|%-s\n",quads[i].op,quads[i].op1,quads[i].op2,quads[i].res);
	}
}
