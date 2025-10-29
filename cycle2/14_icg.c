#include<stdio.h>
#include<ctype.h>
#include<string.h>

char input[20];
char optrstack[20],opndstack[20][20];
int optrtop=-1,opndtop=-1;
int temp_count=0;

int priority(char op){
        switch(op){
                case '+':
                case '-': return 1;
                case '/':
                case '*': return 2;
                default: return 0;
        }
}

void generatecode(){
        char optr=optrstack[optrtop--];
        char opnd1[20],opnd2[20];

        strcpy(opnd2,opndstack[opndtop--]);
        strcpy(opnd1,opndstack[opndtop--]);

        printf("t%d = %s %c %s\n",temp_count,opnd1,optr,opnd2);
        sprintf(opndstack[++opndtop],"t%d",temp_count++);
}

void main(){
        printf("Enter an arithmetic expression: ");
        scanf(" %[^\n]",input);

        int i=0;
        while(input[i]!='\0'){
                if(isalnum(input[i])){
                        char opnd[20];
                        int j=0;
                        while(isalnum(input[i])){
                                opnd[j++]=input[i++];
                        }
                        opnd[j]='\0';
                        strcpy(opndstack[++opndtop],opnd);
                }else if(strchr("+-*/",input[i])){
                        while(priority(optrstack[optrtop])>=priority(input[i])){
                                generatecode();
                        }
                        optrstack[++optrtop]=input[i++];
                }else if(input[i]=='('){
                        optrstack[++optrtop]=input[i++];
                }else if(input[i]==')'){
                        while(optrstack[optrtop]!='('){
                                generatecode();
                        }
                        optrtop--;
                        i++;
                }else{
                        i++;
                }
        }
        while(optrtop!=-1 && opndtop!=-1){
                generatecode();
        }
}
