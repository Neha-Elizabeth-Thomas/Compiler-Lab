#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

void main(int argc,char **argv){
	if(argc<2){
		printf("Usage ./a.out <input filename>\n");
		return;
	}
	FILE* f=fopen(argv[1],"r");
	int state=0,flag=0;
	char ch,c;
	char kw[][10]={"while","for","if","do","switch","case","default","int","float","char"},word[100];

	while(!flag){
		ch=fgetc(f);
		if(ch==EOF)
			flag=1;
		switch(state){
			case 0:
				if(isalnum(ch)||ch=='_'){
					if(isalpha(ch)||ch=='_'){
						fseek(f,-1,SEEK_CUR);
						state=1;//identifier
					}else{
						fseek(f,-1,SEEK_CUR);
						state=3;//integer
					}
				}else if(ch=='/'){
					state=4;//sigle,multi,ass,arith
				}else if(ch=='<' || ch=='>' || ch=='='){
					c=fgetc(f);
					if(c=='='){
						printf("%c= is a relational opertor\n",ch);

					}else if(ch=='='){
						printf("= is an assignment operator\n");
						fseek(f,-1,SEEK_CUR);
					}else{
						printf("%c is a relational operaor\n",ch);
						fseek(f,-1,SEEK_CUR);
					}
				}else if(ch=='&'||ch=='|'){
					c=fgetc(f);
					if(ch=='&' && c=='&' || ch=='|' && c=='|'){
						printf("%c%c is a relational operator\n",ch,c);
					}else{
						printf("%c is a bitwise operator\n",ch);
						fseek(f,-1,SEEK_CUR);
					}
				}else if(ch=='+' || ch=='-' || ch=='%',ch=='*'){
					c=fgetc(f);
					if(c=='='){
						printf("%c= is an assignment operator\n",ch);
					}else{
						printf("%c is an arithmetic operator\n",ch);
						fseek(f,-1,SEEK_CUR);
					}
				}else if(ch=='{' || ch=='}' || ch=='[' || ch==']' || ch==';' || ch==','||ch=='(' || ch==')'){
					printf("%c is a punctuator\n",ch);
				}else if(ch=='\"'){
					int p=0;
					while((ch=fgetc(f))!='\"'){
						word[p++]=ch;
					}
					word[p]='\0';
					printf("%s is a string literal\n",word);
				}
				break;
			case 1:
				int p=0;
				word[p++]=ch;
				while(isalnum(ch=fgetc(f)) || ch=='_'){
					word[p++]=ch;
				}
				fseek(f,-1,SEEK_CUR);
				word[p]='\0';
				state=2;
				break;
			case 2:
				fseek(f,-1,SEEK_CUR);
				int id=1;
				for(int i=0 ; i<10 ; i++){
					if(strcmp(word,kw[i])==0){
						printf("%s is a keyword\n",word);
						id=0;
						break;
					}
				}
				if(id){
					printf("%s is an identifier\n",word);
				}
				state=0;
				break;
			case 3: 
				p=0;
				word[p]=ch;
				while(isdigit(ch=fgetc(f))){
					word[p++]=ch;
				}
				if(isalnum(ch)||ch=='_'){
					printf("Invalid token\n");
					break;
				}
				fseek(f,-1,SEEK_CUR);
				word[p]='\0';
				printf("%s is integer\n",word);
				state=0;
				break;
			case 4:
				if(ch=='*'){
					state=6;
				}else if(ch=='/'){
					state=5;
				}else if(ch=='='){
					printf("/= is an assignment operator\n");
					state=0;
				}else{
					fseek(f,-1,SEEK_CUR);
					printf("/ is an arithmetic operator\n");
					state=0;
				}
				break;
			case 5:
				while(fgetc(f)!='\n');
				printf("Single line comment ignored\n");
				state=0;
				break;
			case 6:
				while(fgetc(f)!='*');
				c=fgetc(f);
				if(c=='/'){
					printf("multi line comment ignored\n");
					state=0;
				}else{
					state=6;
				}
				break;
			default:
				break;
		}
	}

	fclose(f);
}
