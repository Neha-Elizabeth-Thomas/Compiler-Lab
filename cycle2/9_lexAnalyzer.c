#include<stdio.h>
#include<ctype.h>
#include<string.h>

#define LENGTH 20
#define NUM_OF_KEYWORDS 8

void main(int argc,char* argv[]){
        FILE* fp=fopen(argv[1],"r");

        int state=0;
        int flag=0;
        int ch;
        char keywords[20][20]={
        "if","else","switch","case","while","return","int","char"
        };
        while(!flag){
                switch(state){
                        case 0:
                                ch=fgetc(fp);
                                if(ch==EOF){
                                        flag=1;
                                        break;
                                }
                                if(isalpha(ch) || ch=='_'){
                                        fseek(fp,-1,SEEK_CUR);
                                        state=2;
                                }else if(isdigit(ch)){
                                        fseek(fp,-1,SEEK_CUR);
                                        state=3;
                                }

                                else if(ch=='<' || ch=='>' || ch=='=' || ch=='!'){
                                        int nextc=fgetc(fp);
                                        if(nextc=='='){
                                                printf("%c%c is a RELATIONAL OPERATOR\n",ch,nextc);
                                        }else{
                                                if(ch=='='){
                                                        printf("%c is a ASSIGNMENT OPERATOR\n",ch);
                                                }else if(ch=='!'){
                                                        printf("%c is a LOGICAL OPERATOR\n",ch);
                                                }else{
                                                        printf("%c is a RELATIONAL OPERATOR\n",ch);
                                                }
                                                fseek(fp,-1,SEEK_CUR);
                                        }
                                }

                                else if(ch=='&' || ch=='|'){
                                        int nextc=fgetc(fp);
                                        if(nextc==ch){
                                                printf("%c%c is a LOGICAL OPERATOR\n",ch,nextc);
                                        }else{
                                                printf("%c is a BITWISE OPERATOR\n",ch);
                                                fseek(fp,-1,SEEK_CUR);
                                        }
                                }

                                else if(ch=='+' || ch=='-' || ch=='/' || ch=='*' || ch=='%'){
                                        int nextc=fgetc(fp);
                                        if(ch=='/' && nextc=='/'){
                                                int c;
                                                while((c=fgetc(fp))!='\n' && c!=EOF);
                                                printf("SKIPPED SINGLE LINE COMMENT\n");
                                        }else if(ch=='/' && nextc=='*'){
                                                int prev=ch;
                                                while(prev!='*' || ch!='/'){
                                                        prev=ch;
                                                        ch=fgetc(fp);
                                                }
                                                printf("SKIPPED MULTI LINE COMMENT\n");
                                        }else if(nextc=='='){
                                                printf("%c%c is a ASSIGNMENT OPERATOR\n",ch,nextc);
                                        }else{
                                                printf("%c is a ARITHMETIC OPERATOR\n",ch);
                                                fseek(fp,-1,SEEK_CUR);
                                        }
                                }

                                else if(ch=='\"'){
                                        char word[20];
                                        int p=0;
                                        word[p++]='\"';
                                        while((ch=fgetc(fp))!='\"')
                                                word[p++]=ch;
                                        word[p]='\"';
                                        word[p+1]='\0';
                                        printf("%s is a STRING LITERAL\n",word);
                                }

                                else if(ch==',' || ch==';' || ch=='{' || ch=='}' || ch=='(' || ch==')'){
                                        printf("%c is a PUNCTUATOR\n",ch);
                                }
                                break;
                        case 2:
                                char word[LENGTH];
                                int p=0;
                                while(isalnum(ch=fgetc(fp)) || ch=='_'){
                                        word[p++]=ch;
                                }
                                word[p]='\0';
                                int i;
                                for(i=0 ; i<NUM_OF_KEYWORDS ; i++){
                                        if(strcasecmp(word,keywords[i])==0){
                                                printf("%s is a KEYWORD\n",word);
                                                break;
                                        }
                                }
                                if(i==NUM_OF_KEYWORDS){
                                        printf("%s is an IDENTIFIER\n",word);
                                }
                                state=0;
                                break;

                        case 3:
                                //char word[LENGTH];
                                p=0;
                                while(isdigit(ch=fgetc(fp))){
                                        word[p++]=ch;
                                }
                                word[p]='\0';
                                printf("%s is a NUMBER\n",word);
                                state=0;
                                break;
                }
        }
}









