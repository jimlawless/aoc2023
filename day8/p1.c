#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <ctype.h>

void quit(char *msg1,char *msg2) {
    fprintf(stderr,"Error: %s %s\n",msg1,msg2);
    exit(1);
}

#define MAX_NODE ((26*26*26)+1)

 typedef struct  {
    int left;
    int right;
} node_t;


int node_to_int(char *node) {
    int result;
    result=(node[0]-'A')*26*26;
    result+=((node[1]-'A')*26);
    result+=(node[2]-'A');
    //printf("%s == %d\n",node,result);
    return result;
}

int main(int argc,char **argv) {
#define MAX_BUFF (1024)
    FILE *fin;
    char *p;
    char buff[MAX_BUFF];
    char left_right[MAX_BUFF];
    node_t nodes[MAX_NODE];
    int i;
    int count;
    int ndx,left,right;
    int zzz;
    
    fin=fopen(argv[1],"r");
    if(fin==NULL) 
        quit("Can't open input file",argv[1]);
    memset(left_right,0,MAX_BUFF);
    fgets(left_right,MAX_BUFF-1,fin);
    left_right[strlen(left_right)-1]=0;
    fgets(buff,MAX_BUFF-1,fin);
    for(;;) {
        memset(buff,0,MAX_BUFF);        
        if(fgets(buff,MAX_BUFF-1,fin)==NULL) 
            break;
        if(strlen(buff)==0)
            continue;
        buff[strlen(buff)-1]=0;

        p=strtok(buff," \t=(,)");
        ndx=node_to_int(p);
        p=strtok(NULL," \t=(,)");
        nodes[ndx].left=node_to_int(p);
        p=strtok(NULL," \t=(,)");
        nodes[ndx].right=node_to_int(p);
        
    }
    fclose(fin);

    i=node_to_int("AAA");
    zzz=node_to_int("ZZZ");
    p=left_right;
    for(count=1;;count++) {
        if(*p=='L') 
            i=nodes[i].left;
        else
            i=nodes[i].right;
        
        //printf("%c %4d moving to %d\n",*p,count,i);

        if(i==zzz)
            break;
        p++;
        if(!*p)
            p=left_right;
    }    
    printf("Count is %d\n",count);
}
