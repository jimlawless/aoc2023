#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <ctype.h>

void quit(char *msg1,char *msg2) {
    fprintf(stderr,"Error: %s %s\n",msg1,msg2);
    exit(1);
}

#define MAX_RANGE (1000)

typedef struct {
    long long int dest;
    long long int src;
    long long int length;
} range_t ;

range_t seed_to_soil[MAX_RANGE];
range_t soil_to_fertilizer[MAX_RANGE];
range_t fertilizer_to_water[MAX_RANGE];
range_t water_to_light[MAX_RANGE];
range_t light_to_temperature[MAX_RANGE];
range_t temperature_to_humidity[MAX_RANGE];
range_t humidity_to_location[MAX_RANGE];
long long int seeds_used[MAX_RANGE];
int seed_count;

typedef enum {
    INIT,
    SEED_TO_SOIL,
    SOIL_TO_FERTILIZER,
    FERTILIZER_TO_WATER,
    WATER_TO_LIGHT,
    LIGHT_TO_TEMPERATURE,
    TEMPERATURE_TO_HUMIDITY,
    HUMIDITY_TO_LOCATION
} states_t ;


long long int smallest_location;
long long int rn_find(range_t *rn,long long int src);
void rn_set(range_t *rn,long long int dest, long long int src, long long int length);

int main(int argc,char **argv) {
#define MAX_BUFF (1024)
    FILE *fin;
    char *p;
    char buff[MAX_BUFF];
    int i,j;
    states_t state;
    long long int v1,v2,range;
    long long int location,tmp;
    
    printf("long long %d\n",sizeof(long long int));
    fin=fopen(argv[1],"r");
    if(fin==NULL) 
        quit("Can't open input file",argv[1]);

    state=INIT;
    seed_count=0;
    for(i=0;i<MAX_RANGE;i++) {
        seed_to_soil[i].length=-1;
        soil_to_fertilizer[i].length=-1;
        fertilizer_to_water[i].length=-1;
        water_to_light[i].length=-1;
        light_to_temperature[i].length=-1;
        temperature_to_humidity[i].length=-1;
        humidity_to_location[i].length=-1;
        seeds_used[i]=-1;
    }
    
    smallest_location=0x7fffffff;
    for(;;) {
        memset(buff,0,MAX_BUFF);        
        if(fgets(buff,MAX_BUFF-1,fin)==NULL) 
            break;
        if(strlen(buff)<=1)
            continue;
        
        buff[strlen(buff)-1]=0; 
        p=strtok(buff," \t");
        if(isdigit(*p)) {
            switch(state) {
                case INIT:
                    break;
                case SEED_TO_SOIL:
                    v2=atoll(p);
                    p=strtok(NULL," \t");
                    v1=atoll(p);
                    p=strtok(NULL," \t");
                    range=atoll(p);
                    rn_set(seed_to_soil,v1,v2,range);
                    break;
                case SOIL_TO_FERTILIZER:   
                    v2=atoll(p);
                    p=strtok(NULL," \t");
                    v1=atoll(p);
                    p=strtok(NULL," \t");
                    range=atoll(p); 
                    rn_set(soil_to_fertilizer,v1,v2,range);
                    break;                
                case FERTILIZER_TO_WATER:
                     v2=atoll(p);
                    p=strtok(NULL," \t");
                    v1=atoll(p);
                    p=strtok(NULL," \t");
                    range=atoll(p); 
                    rn_set(fertilizer_to_water,v1,v2,range);
                    break;         
                case WATER_TO_LIGHT:
                    v2=atoll(p);
                    p=strtok(NULL," \t");
                    v1=atoll(p);
                    p=strtok(NULL," \t");
                    range=atoll(p);
                    rn_set(water_to_light,v1,v2,range);
                    break;                
                case LIGHT_TO_TEMPERATURE:
                    v2=atoll(p);
                    p=strtok(NULL," \t");
                    v1=atoll(p);
                    p=strtok(NULL," \t");
                    range=atoll(p); 
                    rn_set(light_to_temperature,v1,v2,range);
                    break;
                case TEMPERATURE_TO_HUMIDITY:
                     v2=atoll(p);
                    p=strtok(NULL," \t");
                    v1=atoll(p);
                    p=strtok(NULL," \t");
                    range=atoll(p);
                    rn_set(temperature_to_humidity,v1,v2,range);
                    break;               
                case HUMIDITY_TO_LOCATION:               
                    v2=atoll(p);
                    p=strtok(NULL," \t");
                    v1=atoll(p);
                    p=strtok(NULL," \t");
                    range=atoll(p);
                    rn_set(humidity_to_location,v1,v2,range);
                    break;
                default:
                    fprintf(stderr,"Error! %s state %d",p,state);
                    exit(1);
            }
        }
        else {
            if(!strcmp(p,"seeds:")) {
                p=strtok(NULL," \t");
                while (p!=NULL) {
                    if(!isdigit(*p))
                        break;
                    tmp=atoll(p);
                    seeds_used[seed_count]=tmp;
                    seed_count++;
                    p=strtok(NULL," \t");
                }
                continue;
            }
            else
            if(!stricmp(p,"seed-to-soil")) {
                state=SEED_TO_SOIL;
                continue;
            }
            else 
            if(!stricmp(p,"soil-to-fertilizer")) {
                state=SOIL_TO_FERTILIZER;
                continue;
            }
            else
            if(!stricmp(p,"fertilizer-to-water")) {
                state=FERTILIZER_TO_WATER;
                continue;
            }
            else
            if(!stricmp(p,"water-to-light")) {
                state=WATER_TO_LIGHT;
                continue;
            }
            else
            if(!stricmp(p,"light-to-temperature")) {
                state=LIGHT_TO_TEMPERATURE;
                continue;
            }
            else
            if(!stricmp(p,"temperature-to-humidity")) {
                state=TEMPERATURE_TO_HUMIDITY;
                continue;
            }
            else
            if(!stricmp(p,"humidity-to-location")) {
                state=HUMIDITY_TO_LOCATION;
                continue;
            }else {
                state=INIT;
            }
        }    
    }
    fclose(fin);
    for(i=0;i<seed_count;i++) {
        printf("%lld ",seeds_used[i]);
        tmp=rn_find(seed_to_soil,(long long int)seeds_used[i]);
        printf("%lld ",tmp);
        tmp=rn_find(soil_to_fertilizer,tmp);
        printf("%lld ",tmp);
        tmp=rn_find(fertilizer_to_water,tmp);
        printf("%lld ",tmp);
        tmp=rn_find(water_to_light,tmp);
        printf("%lld ",tmp);
        tmp=rn_find(light_to_temperature,tmp);
        printf("%lld ",tmp);
        tmp=rn_find(temperature_to_humidity,tmp);
        printf("%lld ",tmp);
        location=rn_find(humidity_to_location,tmp);
        printf("Location %lld\n",location);
        if(location<smallest_location)
            smallest_location=location;
    }
    printf("Smallest location: %lld\n",smallest_location);
}

long long int rn_find(range_t *rp,long long int src) {
    int i;
    long long int diff;
    for(i=0;i<MAX_RANGE;i++) {
        if( (src>=rp[i].src)&&(src<=(rp[i].src+rp[i].length))) {
            diff=src-rp[i].src;
            return diff+rp[i].dest;
        }
    }
    return src;
}
void rn_set(range_t *rp,long long int src, long long int dest, long long int length) {
    int i;
    for(i=0;i<MAX_RANGE;i++) {
        if(rp[i].length==-1) {
            rp[i].src=src;
            rp[i].dest=dest;
            rp[i].length=length;
            return;
        }
    }
    quit("rn_set","max");
}
