#include "header.h"

int main(void){
    POTArr pa;
    for(int i = 0; i < MAX_SCENARIO; i++){
        initPOT(&pa.p[i]);
    }
    
    insertToPOT(&pa.p[0], (Traffic){1, "PD", 20});
    insertToPOT(&pa.p[0], (Traffic){2, "PM", 12});
    insertToPOT(&pa.p[0], (Traffic){3, "RD", 15});
    insertToPOT(&pa.p[0], (Traffic){4, "RM", 25});
    insertToPOT(&pa.p[0], (Traffic){5, "LD", 20});
    insertToPOT(&pa.p[0], (Traffic){6, "LM", 18});
    insertToPOT(&pa.p[0], (Traffic){7, "DL", 28});
    insertToPOT(&pa.p[0], (Traffic){8, "ML", 35});

    insertToPOT(&pa.p[1], (Traffic){1, "PD", 27});
    insertToPOT(&pa.p[1], (Traffic){2, "RD", 19});
    insertToPOT(&pa.p[1], (Traffic){5, "LD", 15});
    insertToPOT(&pa.p[1], (Traffic){6, "LM", 29});
    insertToPOT(&pa.p[1], (Traffic){7, "DL", 41});

    insertToPOT(&pa.p[2], (Traffic){1, "LM", 30});
    insertToPOT(&pa.p[2], (Traffic){2, "DL", 12});

    trafficToFileWithComma(&pa, MAX_SCENARIO);

    for(int i = 0; i < MAX_SCENARIO; i++){
            getTotalTime(&pa.p[i]);
    }

    return 0;
}