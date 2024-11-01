#ifndef TRAFFIC_HEADER
#define TRAFFIC_HEADER

#include <stdio.h>
#include <string.h>

#define MAX 8
#define MAX_STR_LEN 500

typedef struct {
    int priority;
    char trafficMovement[3];
    int time; // in seconds
} Traffic;

typedef struct {
    Traffic tr[MAX];
    int lastIndex;
} POT;

/*
    Priority | Movement
        8    |   ML     (Main Lane)
        7    |   DL     (Diversion Lane)
        6    |   LM     (Turn Left Main Lane)
        5    |   LD     (Turn Left Diversion Lane)
        4    |   RM     (Turn Right Main Lane)
        3    |   RD     (Turn Right Diversion Lane)
        2    |   PM     (Pedestrian on Main Lane)
        1    |   PD     (Pedestrian on Diversion Lane)
*/


void initPOT(POT *p);
int getParent(int index);
void insertToPOT(POT *p, Traffic data);
void getTotalTime(POT *p); // total time before pedestrian on main lane


void initPOT(POT *p){
    p->lastIndex = -1;
}

int getParent(int index){
    return (index -1) /2;
}

void insertToPOT(POT *p, Traffic data){
    if(p->lastIndex < MAX-1){
        p->tr[++(p->lastIndex)] = data;
        int index;
        for(index = p->lastIndex; 
            getParent(index) >= 0 && p->tr[getParent(index)].priority < p->tr[index].priority;
            index = getParent(index))
        {
            Traffic temp = p->tr[index];
            p->tr[index] = p->tr[getParent(index)];
            p->tr[getParent(index)] = temp;
        }
    }
}

void getTotalTime(POT *p){
    int seconds = 0;
    int minutes = 0;
    for(int i = 0; i <= (p->lastIndex) && p->tr[i].priority != 2; i++){
        int currMinutes = 0;
        seconds += p->tr[i].time;
        if(seconds >= 60){
            currMinutes = seconds / 60;
            minutes += currMinutes;
            seconds -= 60 * currMinutes;
        }
    }
    if(minutes > 0){
        printf("TOAL TIME: %d minutes and %d seconds", minutes, seconds);
    } else {
        printf("TOTAL TIME: %d seconds", seconds);
    }
}

void trafficToFile(POT *p) {
    FILE *fp = fopen("traffic.dat", "w");
    
    if(fp == NULL){
        printf("Error opening file!\n");
        return;
    }
    
    char trafficStr[MAX_STR_LEN] = "";
    char tempStr[50];
    
    for(int i = 0; i <= p->lastIndex; i++) {
        snprintf(tempStr, sizeof(tempStr), 
                "Priority: %d, Movement: %s, Time: %d seconds\n", 
                p->tr[i].priority, 
                p->tr[i].trafficMovement, 
                p->tr[i].time);
        
        strncat(trafficStr, tempStr, sizeof(trafficStr) - strlen(trafficStr) - 1);
    }
    
    fputs(trafficStr, fp);
    
    fclose(fp);
}

#endif