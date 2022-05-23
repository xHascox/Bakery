#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

// TODO (Lukas) Move BREADS_SOLD and TICKS to CLI
#define BREADS_SOLD 2
#define TICKS 5 // Number of ticks before tgtg check

#define NO 0
#define YES 1

// Function that gets called every k TICKS and decides whether a bread type is going to be offered via TGTG
void tgtg(){
    for (int i = 0; i < dynTypes.count; i++){
        if (dynTypes.TgtgBasket[i] == NO){
            if (dynTypes.Sold[i] == NO) {
                dynTypes.TgtgBasket[i]= YES;
                printf("%s was flagged for TGTG\n", dynTypes.types[i]->name);
            }
        }
        dynTypes.Sold[i] = NO;
    }
}

void runTGTG(char** breadTypes, int nbTypes, int* amounts){

    /* Create bread types according to user input */
    initTypeList(nbTypes);
    for(int i = 0; i < nbTypes; i++){
        addType(breadTypes[i], amounts[i]);
    }
    
    /* Sell bread */
    srand(time(NULL));
    int type = 0;

    for (int i=1; i <= BREADS_SOLD; i++) {
        type = rand() % dynTypes.count;
        if (dynTypes.types[type]->nb > 0){
            dynTypes.types[type]->nb -= 1;
            if (dynTypes.TgtgBasket[type] == NO){
                dynTypes.Sold[type] = YES;
            }
            printf("A bread was sold! Type: %s, TGTG: %d\n", dynTypes.types[type]->name, dynTypes.TgtgBasket[type]);
            if (i % TICKS == 0){
                tgtg();
            }
        }
    }
}

/*
int main(int argc, char const *argv[]){
    char* breadtypes[] = {"Croissant", "Zopf", "Tessinerli"};
    int num[3] = {8,9,10}; 
    runTGTG(breadtypes,3,num);
}
*/
