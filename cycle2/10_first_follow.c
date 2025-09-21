#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define SIZE 26
#define LENGTH 20
int num_of_productions;
char productions[SIZE][LENGTH],nonterminals[SIZE],firstset[SIZE][LENGTH],startSymb;

void set_add(char set[],char element){
	if(!strchr(set,element)){
		int idx=strlen(set);
		set[idx++]=element;
		set[idx]='\0';
	}
}

void set_union(char set1[],char set2[]){
	for(int i=0 ; set2[i]!='\0' ; i++){
		set_add(set1,set2[i]);
	}
}

void set_remove(char set[],char element){
	if(!strchr(set,element))
		return;
	else{
		int idx=strchr(set,element)-set;
		while(set[idx]!='\0'){
			set[idx++]=set[idx+1];
		}
	}
}

int is_in_set(char set[],char element){
	return strchr(set,element)?1:0;
}

int getindex(char NT){
	return NT-'A';
}

void printset(char set[]){
	printf("{");
	for(int i=0 ; set[i]!='\0' ; i++){
		printf("%c",set[i]);
		if(set[i+1]!='\0')
			printf(", ");
	}
	printf("}\n");
}

void read_productions(){
	for(int i=0 ; i<num_of_productions ; i++){
		scanf(" %[^\n]",productions[i]);
		set_add(nonterminals,productions[i][0]);
	}
	startSymb=productions[0][0];
}

void calc_first(char symbol,char set[]){
	if(!isupper(symbol)){
		set_add(set,symbol);
		return;
	}

	for(int i=0 ; i<num_of_productions ; i++){
		if(productions[i][0]==symbol){
			for(int j=2 ; productions[i][j]!='\0' ; j++){
				char symb=productions[i][j];
				char temp_first[LENGTH]={'\0'};
				calc_first(symb,temp_first);

				set_union(set,temp_first);
				if(!is_in_set(temp_first,'#')){
					set_remove(set,'#');
					break;
				}
			}
		}
	}
}

void calc_follow(char symbol,char set[]){
	int k;
	if(symbol==startSymb){
		set_add(set,'$');
	}

	for(int i=0 ; i<num_of_productions ; i++){
		for(int j=2 ; productions[i][j]!='\0' ; j++){
			if(productions[i][j]==symbol){
				for(k=j+1 ; productions[i][k]!='\0' ; k++){
					char next_symb=productions[i][k];
					if(next_symb=='\0')
						break;
					if(!isupper(next_symb)){
						set_remove(set,'#');
						set_add(set,next_symb);
						break;
					}else{
						char temp_first[LENGTH]={'\0'};
						strcpy(temp_first,firstset[getindex(next_symb)]);
						set_union(set,temp_first);
						set_remove(set,'#');
						if(!is_in_set(temp_first,'#')){
							break;
						}
						
					}
				}
				if(productions[i][k]=='\0' && productions[i][0]!=symbol){
					char temp[LENGTH];
					calc_follow(productions[i][0],temp);
					set_union(set,temp);
				}
			}
		}
	}
}

void main(){
	printf("How many productions are there? ");
	scanf("%d",&num_of_productions);

	printf("Enter %d productions: ",num_of_productions);
	read_productions();

	printf("FIRST\n");
	for(int i=0 ; nonterminals[i]!='\0' ; i++){
		char temp[LENGTH]={'\0'};
		calc_first(nonterminals[i],temp);
		printf("First %c: ",nonterminals[i]);
		printset(temp);
		strcpy(firstset[getindex(nonterminals[i])],temp);
	}

	printf("FOLLOW\n");
	for(int i=0 ; nonterminals[i] ; i++){
		char temp[LENGTH]={'\0'};
		calc_follow(nonterminals[i],temp);
		printf("Follow %c: ",nonterminals[i]);
		printset(temp);
	}
}
