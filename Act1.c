#include "header.h"

int main(void){
    POT p;
    initPOT(&p);

    insertToPOT(&p, (Traffic){1, "RD", 20});
    insertToPOT(&p, (Traffic){2, "PM", 12});
    insertToPOT(&p, (Traffic){3, "RD", 15});
    insertToPOT(&p, (Traffic){4, "RM", 25});
    insertToPOT(&p, (Traffic){5, "LD", 20});
    insertToPOT(&p, (Traffic){6, "LM", 18});
    insertToPOT(&p, (Traffic){7, "DL", 28});
    insertToPOT(&p, (Traffic){8, "ML", 35});

    trafficToFile(&p);

    getTotalTime(&p);

    return 0;
}