#ifndef TRAFFIC_HEADER
#define TRAFFIC_HEADER

#include <stdio.h>
#include <string.h>

#define MAX 8
#define MAX_STR_LEN 400
#define MAX_SCENARIO 3

typedef struct {
    int priority;
    char trafficMovement[3];
    int time; // in seconds
} Traffic;

typedef struct {
    Traffic tr[MAX];
    int lastIndex;
} POT;

typedef struct {
    POT p[MAX_SCENARIO];
} POTArr;

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
void trafficToFile(POT *p);
void trafficToFileWithComma(POTArr *pa, int size);

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
    int totalSeconds = 0;
    for(int i = 0; i <= (p->lastIndex); i++){
        if(p->tr[i].priority > 2){
            totalSeconds += p->tr[i].time;
        }
    }
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    if(minutes > 0){
        printf("TOTAL TIME: %d minutes and %d seconds\n", minutes, seconds);
    } else {
        printf("TOTAL TIME: %d seconds\n", seconds);
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

void trafficToFileWithComma(POTArr *pa, int size){
    FILE *fp = fopen("traffic_result.dat", "w");
    
    if(fp == NULL){
        printf("Error opening file!\n");
        return;
    }
    
    char trafficStr[MAX_STR_LEN * MAX_SCENARIO] = "";
    char tempStr[50];

    for(int i = 0; i < size; i++){
        snprintf(tempStr, sizeof(tempStr), "Scenario %d:\n", i + 1);
        strncat(trafficStr, tempStr, sizeof(trafficStr) - strlen(trafficStr) - 1);
        
        for(int j = 0; j <= pa->p[i].lastIndex; j++) {
            snprintf(tempStr, sizeof(tempStr), 
                    "Priority: %d, Movement: %s, Time: %d seconds\n", 
                    pa->p[i].tr[j].priority, 
                    pa->p[i].tr[j].trafficMovement, 
                    pa->p[i].tr[j].time);
            
            strncat(trafficStr, tempStr, sizeof(trafficStr) - strlen(trafficStr) - 1);
        }
        
        if(i < size - 1) {
            strncat(trafficStr, "\n", sizeof(trafficStr) - strlen(trafficStr) - 1);
        }
    }
    
    fputs(trafficStr, fp);
    
    fclose(fp);
}

#endif