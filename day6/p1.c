#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <ctype.h>

void quit(char *msg1,char *msg2) {
    fprintf(stderr,"Error: %s %s\n",msg1,msg2);
    exit(1);
}



int main(int argc,char **argv) {
#define MAX_BUFF (1024)
    FILE *fin;
    char *p;
    char buff[MAX_BUFF];
    int i,j;
#define MAX_RUNS (10)
    int t[MAX_RUNS];
    int count=0;
    int d[MAX_RUNS];
    int total=1;
    int more;
    int distance;
    
    fin=fopen(argv[1],"r");
    if(fin==NULL) 
        quit("Can't open input file",argv[1]);
    memset(buff,0,MAX_BUFF);        
    fgets(buff,MAX_BUFF-1,fin);
    buff[strlen(buff)-1]=0;
    p=strtok(buff,": \t");
    for(;;) {
        p=strtok(NULL," \t");
        if(p==NULL)
            break;
        t[count]=atoi(p);
        count++;
    }
    count=0;
    memset(buff,0,MAX_BUFF);        
    fgets(buff,MAX_BUFF-1,fin);
    buff[strlen(buff)-1]=0;
    p=strtok(buff,": \t");
    for(;;) {
        p=strtok(NULL," \t");
        if(p==NULL)
            break;
        d[count]=atoi(p);
        count++;
    }
    for(i=0;i<count;i++) {
        more=0;
        for(j=1;j<t[i]-1;j++) {
            distance=j*(t[i]-j);
            if((distance > d[i]) )
                more++;
        }
        if(more>0) 
            total*=more;
    }
    
    fclose(fin);
    printf("Total: %d\n",total);
}
