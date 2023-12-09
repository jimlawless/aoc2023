#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <ctype.h>

void quit(char *msg1,char *msg2) {
    fprintf(stderr,"Error: %s %s\n",msg1,msg2);
    exit(1);
}    
    typedef enum {
        EMPTY=0,
        TWO=2,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        JACK,
        QUEEN,
        KING,
        ACE,
        HIGH_CARD,
        TWO_OF_A_KIND,
        TWO_PAIR,
        THREE_OF_A_KIND,
        FULL_HOUSE,
        FOUR_OF_A_KIND,
        FIVE_OF_A_KIND
    } sequence_t;
    
    
#define MAX_CARDS (5)
    typedef struct  {
        sequence_t seq;
        char original[MAX_CARDS+1];
        sequence_t encoded[MAX_CARDS];
        int bid;
    } hand_t ;
    
#define MAX_HANDS (2000)
    hand_t hands[MAX_HANDS];
    int hand_count;    

    hand_t *hand;
    
#define MAX_FACE_CARDS (FIVE_OF_A_KIND+1)    
    int faces[MAX_FACE_CARDS];
    
void print_card(sequence_t i);

int compare_hands(const void *v1, const void *v2) {
    hand_t *h1,*h2;
    sequence_t *p1,*p2;
    int i;
    
    h1=(hand_t *)v1;
    h2=(hand_t *)v2;
    if(h1->seq<h2->seq)
        return -1;
    if(h1->seq>h2->seq)
        return 1;
    
    p1=h1->encoded;
    p2=h2->encoded;
    while(*p1) {
        if(*p1>*p2) 
            return 1;
        if(*p1<*p2)
            return -1;
        p1++;
        p2++;
    }
    return 0;    
}

int main(int argc,char **argv) {
#define MAX_BUFF (1024)
    FILE *fin;
    char *p;
    char buff[MAX_BUFF];
    int i,j;
    int total;
        
    fin=fopen(argv[1],"r");
    if(fin==NULL) 
        quit("Can't open input file",argv[1]);
    hand_count=0;
    total=0;
    for(;;) {
        for(i=0;i<MAX_FACE_CARDS;i++)
            faces[i]=0;
        memset(buff,0,MAX_BUFF);        
        if(fgets(buff,MAX_BUFF-1,fin)==NULL) 
            break;
        if(strlen(buff)==0)
            continue;
        buff[strlen(buff)-1]=0;
        hand=hands+hand_count;
        hand_count++;       
        p=strtok(buff," \t");
 
        j=0;
        while(*p) {
            hand->original[j]=*p;
            switch(*p) {
                case 'A':
                    faces[(int)ACE]++;
                    hand->encoded[j]=ACE;
                    break;
                
                case 'K':
                    faces[(int)KING]++;
                    hand->encoded[j]=KING;
                    break;
                
                case 'Q':
                    faces[(int)QUEEN]++;
                    hand->encoded[j]=QUEEN;
                    break;

                case 'J':
                    faces[(int)JACK]++;
                    hand->encoded[j]=JACK;
                    break;

                case 'T':
                    faces[(int)TEN]++;
                    hand->encoded[j]=TEN;
                    break;
                    
                case '2': case '3': case '4': case '5':
                case '6': case '7': case '8': case '9':
                    faces[(int)(*p-'0')]++;
                    hand->encoded[j]=(int) (*p-'0');
                    break;
                default:
                    quit("Unknown character",p);
            }
            j++;
            p++;
        }
        hand->seq=0;
        
        for(i=0;i<=ACE;i++) {
            switch(faces[i]) {
                case 0:
                case 1:
                    continue;
                    
                case 2:
                    faces[TWO_OF_A_KIND]++;
                    if(faces[TWO_OF_A_KIND]==2) {
                        faces[TWO_PAIR]=1;
                        faces[TWO_OF_A_KIND]=0;
                    }
                    break;
                
                case 3:
                    faces[THREE_OF_A_KIND]++;
                    break;
                
                case 4:
                    faces[FOUR_OF_A_KIND]++;
                    break;
                
                case 5:
                    faces[FIVE_OF_A_KIND]++;
                    break;
                default:
                    printf("%d\n",faces[i]);
                    quit("This shouldn't happen.","");
                    break;
                
            }    
        }
        if( (faces[TWO_OF_A_KIND]==1) && (faces[THREE_OF_A_KIND]==1)) {
            faces[FULL_HOUSE]=1;
            faces[TWO_OF_A_KIND]=0;
            faces[THREE_OF_A_KIND]=0;
        }                       
     
        j=0;
        for(i=(int)FIVE_OF_A_KIND;i>HIGH_CARD;i--) {
            if(faces[i]!=0) {
                hand->seq=i;
                break;
            }
        }
        if(hand->seq==0) 
            hand->seq=HIGH_CARD;
        
        p=strtok(NULL," \t");
        hand->bid=atoi(p);
    }
    fclose(fin);
    
    // sort the array of hands
    qsort(hands,hand_count,sizeof(hand_t),compare_hands);
    printf("----\n");
    for(i=0;i<hand_count;i++) {
        printf("%5s ",hands[i].original);
        for(j=0;j<MAX_CARDS;j++) 
            printf("%-2d ",hands[i].encoded[j]);
        
        print_card(hands[i].seq);
        total+=((i+1)*hands[i].bid);
        printf("Bid: %d\n\n",hands[i].bid);
    }
    printf("Total: %d\n",total);
}

void print_card(sequence_t i) {
    switch(i) {
        case TWO:
            printf("TWO ");
            break;

        case THREE:
            printf("THREE ");
            break;

        case FOUR:
            printf("FOUR ");
            break;
                                                
        case FIVE:
            printf("FIVE ");
            break;

        case SIX:
            printf("SIX ");
            break;

        case SEVEN:
            printf("SEVEN ");
            break;

        case EIGHT:
            printf("EIGHT ");
            break;

        case NINE:
            printf("NINE ");
            break;

        case TEN:
            printf("TEN ");
            break;
                                                
        case JACK:
            printf("JACK ");
            break;

        case QUEEN:
            printf("QUEEN ");
            break;

        case KING:
            printf("KING ");
            break;
            
        case ACE:
            printf("ACE ");
            break;
            
        case HIGH_CARD:
            printf("HIGH-CARD ");
            break;
            
        case TWO_OF_A_KIND:
            printf("TWO-OF-A-KIND ");
            break;

        case TWO_PAIR:
            printf("TWO-PAIR ");
            break;

        case THREE_OF_A_KIND:
            printf("THREE-OF-A-KIND ");
            break;

        case FULL_HOUSE:
            printf("FULL-HOUSE ");
            break;
                                                
        case FOUR_OF_A_KIND:
            printf("FOUR-OF-A-KIND ");
            break;

        case FIVE_OF_A_KIND:
            printf("FIVE-OF-A-KIND ");
            break;

        default:
            printf("%d\n",i);
            quit("Should not be here, either.","");
            break;
    }
}
