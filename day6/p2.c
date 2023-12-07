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
    long long int i,j;
    
    long long int more;
    long long int distance;
    long long int t,d;
    
    fin=fopen(argv[1],"r");
    if(fin==NULL) 
        quit("Can't open input file",argv[1]);
    
    t=d=0;
    
    memset(buff,0,MAX_BUFF);        
    fgets(buff,MAX_BUFF-1,fin);
    buff[strlen(buff)-1]=0;
    p=buff;
    while(*p) {
        if(isdigit(*p)) {
            t*=10;
            t+=(long long int) (*p-'0');
        }
        p++;
    }
    
    
    memset(buff,0,MAX_BUFF);        
    fgets(buff,MAX_BUFF-1,fin);
    buff[strlen(buff)-1]=0;
    p=buff;
    while(*p) {
        if(isdigit(*p)) {
            d*=10;
            d+=(long long int) (*p-'0');
        }
        p++;
    }
    printf("%lld %lld\n",t,d);
    more=0;
    for(j=1;j<t-1;j++) {
        distance=j*(t-j);
        if((distance > d) )
            more++;
        
    }
    
    fclose(fin);
    printf("Wins: %lld\n",more);
}