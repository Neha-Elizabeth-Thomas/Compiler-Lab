#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int n,m;
char symb[20];
int transitions[20][20][20],epsilon[20][20],eclosure[20][20];

void addToClosure(int state,int s){
        if(eclosure[state][s]!=1){
                eclosure[state][s]=1;
                for(int i=0 ; i<n ; i++){
                        if(epsilon[s][i]==1)
                                addToClosure(state,i);
                }
        }
}
void compClosure(){
        for(int i=0 ; i<n ; i++)
                addToClosure(i,i);
}

void main(){
//      memset(transitions,0,sizeof(transitions));
//      memset(epsilon,0,sizeof(epsilon));
//      memset(eclosure,0,sizeof(eclosure));

        printf("How many states: ");
        scanf("%d",&n);

        printf("How many symbols: ");
        scanf("%d",&m);

        printf("Enter %d symbols: ",m);
        for(int i=0 ; i<m ; i++)
                scanf(" %c",&symb[i]);

        printf("Enter transitions\n");
        for(int i=0 ; i<n ; i++)
                for(int j=0 ; j<m ; j++){
                        int num;
                        printf("How many States from q%d via symbol %c: ",i,symb[j]);
                        scanf("%d",&num);

                        if(num)
                                printf("Enter %d states: ",num);
                        for(int k=0 ; k<num ; k++){
                                int state;
                                scanf("%d",&state);
                                transitions[i][j][state]=1;
                        }
                }

        printf("\nEnter E transitions(-1,-1) to stop:\n");
        while(1){
                int q1,q2;
                scanf("%d %d",&q1,&q2);
                if(q1==-1 && q2==-1)
                        break;
                epsilon[q1][q2]=1;
        }

        compClosure();

        printf("E closure :\n");
        for(int i=0 ; i<n ; i++){
                printf("FOR STATE Q%d:  ",i);
                for(int j=0 ; j<n ; j++)
                        if(eclosure[i][j]==1){
                                printf("q%d ,",j);
                        }
                printf("\n\n");
        }



        printf("NFA WITHOUT E TRANSITIONS: \n");
        for(int i=0 ; i<n ; i++){
                for(int j=0 ; j<m ; j++){
                        int result[20];
                        memset(result,0,sizeof(result));

                        for(int k=0 ; k<n ; k++){
                                if(eclosure[i][k]==1){
                                        for(int l=0 ; l<n ; l++){
                                                if(transitions[k][j][l]==1){
                                                        for(int p=0 ; p<n ; p++){
                                                                if(eclosure[l][p]==1){
                                                                        result[p]=1;
                                                                }
                                                        }
                                                }
                                        }
                                }
                        }

                        printf("States from q%d via symbol %c:  ",i,symb[j]);
                        for(int k=0 ; k<n ; k++)
                                if(result[k]==1){
                                        printf("q%d  ",k);
                                }
                        printf("\n\n");
                }
        }

}

