#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <ctype.h>

#define ENCODE(x,y) ( (tolower(x)*128)+tolower(y))

int codes[16384];

char *nums[]= { "zero","one","two","three","four","five",
              "six","seven","eight","nine" } ;

int main(int argc,char **argv) {
#define MAX_BUFF (1024)
    FILE *fin;
    char *p;
    int number;
    int sum;
    char buff[MAX_BUFF];
    char c1,c2,tmp;
    int lookup;
    int i;
    
    for(i=0;i<=16384;i++)
        codes[i]=-1;
    
    codes[ENCODE('z','e')]=0;
    codes[ENCODE('o','n')]=1;
    codes[ENCODE('t','w')]=2;
    codes[ENCODE('t','h')]=3;
    codes[ENCODE('f','o')]=4;
    codes[ENCODE('f','i')]=5;
    codes[ENCODE('s','i')]=6;
    codes[ENCODE('s','e')]=7;
    codes[ENCODE('e','i')]=8;
    codes[ENCODE('n','i')]=9;
    
    printf("%d %d\n",ENCODE('a','a'), ENCODE('z','z'));
    
    fin=fopen(argv[1],"r");
    if(fin==NULL) {
        fprintf(stderr,"Can't open %s\n",argv[1]);
        return 1;
    }
    sum=0;
    for(;;) {
        memset(buff,0,MAX_BUFF);        
        if(fgets(buff,MAX_BUFF-1,fin)==NULL) 
            break;
        number=0;
        if(strlen(buff)==0)
            continue;
        buff[strlen(buff)-1]=0;
        printf("%s\n",buff);
        c1='x';
        c2='x';
        for(p=buff;*p;p++) {
            if(isdigit(*p)) {
                if(c1=='x') {
                    c1=*p;
                    continue;
                }
                c2=*p;
            }
            else {
                lookup=codes[ENCODE(p[0],p[1])];
                if(lookup==-1)
                    continue;
                if(strncmp(nums[lookup],p,strlen(nums[lookup]))==0) {
                    if(c1=='x') {
                        c1=('0'+lookup);
                        continue;
                    }
                    else {
                        c2=('0'+lookup);
                    }
                }
            }
        }
        if(c2=='x')
            c2=c1;
        printf("number is %c%c\n",c1,c2);
        number=(c1-'0')*10+(c2-'0');
        sum+=number;
    }        
    printf("Sum is %d\n",sum);
}
