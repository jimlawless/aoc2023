#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <ctype.h>

void quit(char *msg1,char *msg2) {
    fprintf(stderr,"Error: %s %s\n",msg1,msg2);
    exit(1);
}

#define MAX_CARDS (256)
int card_total[MAX_CARDS];
int card_count[MAX_CARDS];

int winning[100];
int win_count;
int total;
int card_max;
int card_num;

int main(int argc,char **argv) {
#define MAX_BUFF (1024)
    FILE *fin;
    char *p;
    char buff[MAX_BUFF];
    int i,j;
    
    fin=fopen(argv[1],"r");
    if(fin==NULL) 
        quit("Can't open input file",argv[1]);
    total=0;
    card_max=0;
    for(i=0;i<MAX_CARDS;i++) 
        card_count[i]=card_total[i]=0;
    for(;;) {
        for(i=0;i<100;i++) 
            winning[i]=0;
        memset(buff,0,MAX_BUFF);        
        if(fgets(buff,MAX_BUFF-1,fin)==NULL) 
            break;
        if(strlen(buff)==0)
            continue;
        card_max++;
        buff[strlen(buff)-1]=0;
        p=strtok(buff," \t");
        p=strtok(NULL,":");
        card_num=atoi(p);
        for(;;) {
            p=strtok(NULL," \t");
            if(*p=='|')
                break;
            i=atoi(p);
            winning[i]=1;
        }
        win_count=0;
        for(;;) {
            p=strtok(NULL," \t");
            if(p==NULL)
                break;
            i=atoi(p);
            if(winning[i])
                win_count++;
        }
        if(win_count!=0) {
            card_count[card_num]++;
            card_total[card_num]+=win_count;
        }

           
    }
    fclose(fin);
  
    for(i=1;i<=card_max;i++) {
        if(card_total[i]==0) {
            // not a winner but we count the card
            total++;
            continue;
        }
        total+=card_count[i];
        while(card_count[i]>0) {

            for(j=i+1;j<=(i+card_total[i]);j++) {
                card_count[j]++;
            }
            card_count[i]--;
        }
    } 
    for(i=0;i<MAX_CARDS;i++)
        total+=card_count[i]; 
    printf("Total: %d\n",total);
}