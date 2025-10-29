#include<stdio.h>
#include<stdlib.h>
#include<string.h>


char productions[][10]={"i","E+E","E-E","E*E","E/E","(E)"};
char nonterminals[]={'E','E','E','E','E','E'};
int num_of_productions=6;

char input[20];
int ip=0;

char stack[20];
int top=-1;

int reduce(){
        for(int i=0 ; i<num_of_productions ; i++){
                int handle_len=strlen(productions[i]);

                if(top+1<handle_len){
                        continue;
                }

                int handle_start=top-handle_len+1;
//              printf("%s\n",&stack[handle_start]);

                if(strcmp(&stack[handle_start],productions[i])==0){
//                      printf("%s\n",&stack[handle_start]);
                        top-=handle_len;
                        stack[++top]=nonterminals[i];
                        stack[top+1]='\0';
                        return i;
                }
        }
        return -1;
}

void print_line(char action[]){
        for(int i=0 ; i<=top ; i++)
                printf("%c",stack[i]);
        printf("\t\t");
        printf("%s\t\t",&input[ip]);
        printf("%s\n",action);
}

void shift(){
        stack[++top]=input[ip];
        stack[top+1]='\0';
}

void main(){
        char action[20];
        printf("Enter an arithmetix expression: ");
        scanf(" %[^\n]",input);

        printf("Stack\t\tInput\t\tAction\n");
        int red_res=1;
        while((red_res=reduce())!=-1 || input[ip]!='\0'){
                if(red_res!=-1){
                        sprintf(action,"Reduce %c->%s",nonterminals[red_res],productions[red_res]);
                        print_line(action);
                }else if(input[ip]!='\0'){
                        shift();
                        ip++;
                        sprintf(action,"Shift %c",input[ip-1]);
                        print_line(action);
                }
        }

        if(stack[top]=='E' && top==0){
                printf("ACCEPTED\n");
        }else{
                printf("REJECTED\n");
        }
}



