#include<stdio.h>
#define LENGTH 20
#define SIZE 10
struct quadruples{
        char op;
        char opnd1[LENGTH];
        char opnd2[LENGTH];
        char res[LENGTH];
}tac[SIZE];
int num_of_instructions;

char* get_mnemonic(char op){
        switch(op){
                case '+': return "ADD";
                case '-': return "SUB";
                case '*': return "MUL";
                case '/': return "DIV";
                default: return "???";
        }
}

void generate_code(){
        for(int i=0  ; i<num_of_instructions ; i++){
                printf("\n%s = %s %c %s\n",tac[i].res,tac[i].opnd1,tac[i].op,tac[i].opnd2);
                if(tac[i].op=='='){
                        printf("MOV AX,%s\n",tac[i].opnd1);
                        printf("MOV %s,AX\n",tac[i].res);
                }else{
                        printf("MOV AX,%s\n",tac[i].opnd1);
                        printf("%s AX,%s\n",get_mnemonic(tac[i].op),tac[i].opnd2);
                        printf("MOV %s,AX\n",tac[i].res);
                }
        }
}

void main(){
        printf("How many instructions: ");
        scanf("%d",&num_of_instructions);

        printf("Enter %d instructions :\n",num_of_instructions);
        for(int i=0 ; i<num_of_instructions ; i++){
                scanf("%s = %s %c %s",tac[i].res,tac[i].opnd1,&tac[i].op,tac[i].opnd2);
                if(tac[i].op=='_')
                        tac[i].op='=';

        }

        generate_code();
}
