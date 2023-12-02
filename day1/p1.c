#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <ctype.h>

int main(int argc,char **argv) {
#define MAX_BUFF (1024)
    FILE *fin;
    char *p;
    int number;
    int sum;
    char buff[MAX_BUFF];
    char c1,c2,tmp;
    
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
        }
        if(c2=='x')
            c2=c1;
        printf("number is %c%c\n",c1,c2);
        number=(c1-'0')*10+(c2-'0');
        sum+=number;
    }        
    fclose(fin);
    printf("Sum is %d\n",sum);
}
