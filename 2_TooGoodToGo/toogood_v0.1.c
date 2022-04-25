#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define BREAD_TYPES 5 // Number of different bread types
#define BREADS_SOLD 20 // Must be less than MAX_BREAD
#define TICKS 5 // Number of ticks before tgtg check

#define CROISSANT 0
#define ZOPF 1
#define TESSINERLI 2
#define BURLI 3
#define PUMPERNIKEL 4

#define NO 0
#define YES 1

// Blueprint for different types of breads
struct BreadType {
    int id; // Identifier
    char name[64]; // Name of bread type
    int nb; // Number of breads of this type
};

// The types of bread the bakery offers
struct BreadType types[BREAD_TYPES];

// The types sold in the last k TICKS
int Sold[BREAD_TYPES];

// The types that are currently offered over TGTG
int TgtgBasket[BREAD_TYPES];

// Function that gets called every k TICKS and decides whether a bread type is going to be offered via TGTG
void tgtg(){
    for (int i = 0; i < BREAD_TYPES; i++){
        if (TgtgBasket[i] == NO){
            if (Sold[i] == YES) {
                TgtgBasket[i] = YES;
                printf("%s was flagged for TGTG\n", types[i].name);
            }
        }
        Sold[i] = NO;
    }
}


int main(){

    // (0) Initialization
    for (int i = 0; i < BREAD_TYPES; i++){
        Sold[i] = NO;
        TgtgBasket[i] = NO;
    }

    //(1) Create bread
    strcpy(types[CROISSANT].name, "Croissant");
    types[CROISSANT].nb = 4;

    strcpy(types[ZOPF].name, "Zopf");
    types[ZOPF].nb = 4;

    strcpy(types[TESSINERLI].name, "Tessinerli");
    types[TESSINERLI].nb = 4;

    strcpy(types[BURLI].name, "Bürli");
    types[BURLI].nb = 4;

    strcpy(types[PUMPERNIKEL].name, "Pumpernikel");
    types[PUMPERNIKEL].nb = 4;
        
            
    //(2) Sell bread
    srand(time(NULL));
    int type = 0;

    for (int i=1; i <= BREADS_SOLD; i++) {
        type = rand() % BREAD_TYPES;
        if (types[type].nb > 0){
            types[type].nb -= 1;
            if (TgtgBasket[type] == NO){
                Sold[type] = YES;
            }
            printf("A bread was sold! Type: %s, TGTG: %d\n", types[type].name, TgtgBasket[type]);
            if (i % TICKS == 0){
                tgtg();
            }
        }
    }
                 
    return 0;
}


