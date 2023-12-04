#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <ctype.h>

void quit(char *msg1,char *msg2) {
    fprintf(stderr,"Error: %s %s\n",msg1,msg2);
    exit(1);
}

int winning[100];
int win_count;
int total;

int main(int argc,char **argv) {
#define MAX_BUFF (1024)
    FILE *fin;
    char *p;
    char buff[MAX_BUFF];
    int i;
    
    fin=fopen(argv[1],"r");
    if(fin==NULL) 
        quit("Can't open input file",argv[1]);
    total=0;
    for(;;) {
        for(i=0;i<100;i++) 
            winning[i]=0;
        memset(buff,0,MAX_BUFF);        
        if(fgets(buff,MAX_BUFF-1,fin)==NULL) 
            break;
        if(strlen(buff)==0)
            continue;
        buff[strlen(buff)-1]=0;
        p=strtok(buff,":");
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
                win_count = (win_count == 0) ? 1 : win_count * 2;
                
        }
        total+=win_count;    
    }
    fclose(fin);
    printf("Total: %d\n",total);
}
