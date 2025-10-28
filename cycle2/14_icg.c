#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define MAXSIZE 100

char opnd_stack[MAXSIZE][MAXSIZE],optr_stack[MAXSIZE];
int opnd_top=-1,optr_top=-1,temp_count=0;

int priority(char op){
        switch(op){
                case '+':
                case '-': return 1;
                case '*':
                case '/': return 2;
        }
}

void generate_code(){
//      printf("A\n");
        char optr=optr_stack[optr_top--];
        char opnd2[20],opnd1[20];
        strcpy(opnd2,opnd_stack[opnd_top--]);
        strcpy(opnd1,opnd_stack[opnd_top--]);

        printf("t%d = %s %c %s\n",temp_count,opnd1,optr,opnd2);
        sprintf(opnd_stack[++opnd_top],"t%d",temp_count++);
}

void main(){
        char expn[100];
        int i;

        printf("ENter an expression: ");
        scanf(" %[^\n]",expn);

        i=0;
        while(expn[i]!='\0'){
                if(isalnum(expn[i])){
                        char opnd[100];
                        int j=0;
                        while(isalnum(expn[i])){
                                opnd[j++]=expn[i++];
                        }
                        opnd[j]='\0';
                        strcpy(opnd_stack[++opnd_top],opnd);
                }else if(strchr("+-*/",expn[i])){
                        while(optr_top>-1 && priority(optr_stack[optr_top])>=priority(expn[i])){
                                generate_code();
                        }
                        optr_stack[++optr_top]=expn[i++];
                }else{
                        i++;
                }
        }
        while(optr_top>-1 && opnd_top>-1){
                generate_code();
        }
}
