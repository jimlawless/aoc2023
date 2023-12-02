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
    int game_num;
    int count;
    int possible;
    int sum;
    #define MAX_RED (12)
    #define MAX_GREEN (13)
    #define MAX_BLUE (14)
    int red_min;
    int green_min;
    int blue_min;
    
    fin=fopen(argv[1],"r");
    if(fin==NULL) 
        quit("Can't open input file",argv[1]);
    sum=0;
    for(;;) {
        possible=1;
        red_min=green_min=blue_min=0;
        
        memset(buff,0,MAX_BUFF);        
        if(fgets(buff,MAX_BUFF-1,fin)==NULL) 
            break;
        if(strlen(buff)==0)
            continue;
        buff[strlen(buff)-1]=0;
        p=strtok(buff," \t");
        if(p==NULL)
            quit("Missing Game string","NULL");
        if(strcmp(p,"Game")!=0)
            quit("Illegal firsst token ",p);
        
        p=strtok(NULL,":");
        if(p==NULL)
            quit("Missing colon","");
        game_num=atoi(p);
        
        for(;;) {
            p=strtok(NULL," ,;");
            if(p==NULL)
                break;
            count=atoi(p);
            p=strtok(NULL," ,;");
            if(!stricmp(p,"red")) {
                if(count>red_min)
                    red_min=count;                    
            }
            else
            if(!stricmp(p,"green")) {
                if(count>green_min)
                    green_min=count;                    
            }
            else
            if(!stricmp(p,"blue")) {
                if(count>blue_min)
                    blue_min=count;                    
                
            }                
            else
                quit("Unknown value",p);
        }
        sum+=(red_min*green_min*blue_min);
            //printf("sum is %d\n",sum);
    }
    fclose(fin);
    printf("Power sum: %d\n",sum);
}