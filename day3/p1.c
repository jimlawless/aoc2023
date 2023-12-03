#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <ctype.h>

int count;
int width;

void quit(char *msg1,char *msg2) {
    fprintf(stderr,"Error: %s %s\n",msg1,msg2);
    exit(1);
}

int check_char(char **schm,int x,int y) {
    if((x<0)||(y<0)||(x>=width)||(y>=count))
        return 0;
    return (!isdigit(schm[y][x])) && (schm[y][x]!='.');   
}

int is_adjacent(char **schm,int x, int y) {
    if(check_char(schm,x-1,y-1))
        return 1;
    if(check_char(schm,x,y-1))
        return 1;
    if(check_char(schm,x+1,y-1))
        return 1;
    if(check_char(schm,x+1,y))
        return 1;
    if(check_char(schm,x+1,y+1))
        return 1;
    if(check_char(schm,x,y+1))
        return 1;
    if(check_char(schm,x-1,y+1))
        return 1;
    if(check_char(schm,x-1,y))
        return 1;
    return 0;
}

int main(int argc,char **argv) {
#define MAX_BUFF (1024)
    FILE *fin;
    char *p;
    char buff[MAX_BUFF];

    char **schm;
    int i,j,adj;
    int a,sum;
    
    fin=fopen(argv[1],"r");
    if(fin==NULL) 
        quit("Can't open input file",argv[1]);
    memset(buff,0,MAX_BUFF);
    if(fgets(buff,MAX_BUFF-1,fin)==NULL) 
        quit("Error in file",argv[1]);
    buff[strlen(buff)-1]=0;
    width=strlen(buff);
    count=1;
    for(;;) {
        memset(buff,0,MAX_BUFF);
        if(fgets(buff,MAX_BUFF-1,fin)==NULL) 
            break;
        if(strlen(buff)<=1)
            continue;
        count++;
    }  
    fclose(fin);    
    schm=(char **)malloc(sizeof(char *)*(width+1));    

    fin=fopen(argv[1],"r");
    for(i=0;;) {
        memset(buff,0,MAX_BUFF);        
        if(fgets(buff,MAX_BUFF-1,fin)==NULL) 
            break;
        if(strlen(buff)<=1)
            continue;
        buff[strlen(buff)-1]=0;
        schm[i]=(char *)malloc(strlen(buff)+1);
        strcpy(schm[i],buff);
        i++;
    }
    fclose(fin);
    printf("Width: %d Count: %d\n",width,count);
    sum=0;
    a=0;
    for(i=0;i<count;i++) {
        adj=0;
        for(j=0;j<width;j++) {
            if(isdigit(schm[i][j])) {
                a*=10;
                a+=(schm[i][j])-'0';
                if(is_adjacent(schm,j,i))
                    adj=1;
            }
            else {
                if(a!=0) {
                    if(adj)
                        sum+=a;
                    a=0;
                    adj=0;
                }
            }
        }
        if(a!=0) {
            if(adj)
                sum+=a;
            a=0;
            adj=0;
        }
    }
    printf("Sum: %d\n",sum);
}
