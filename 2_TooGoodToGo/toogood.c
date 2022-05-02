#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

//#define BREAD_TYPES 5 // Number of different bread types
#define BREADS_SOLD 20 // Must be less than MAX_BREAD
#define TICKS 5 // Number of ticks before tgtg check
/*
#define CROISSANT 0
#define ZOPF 1
#define TESSINERLI 2
#define BURLI 3
#define PUMPERNIKEL 4
*/
#define NO 0
#define YES 1

// Blueprint for different types of breads
struct BreadType {
    int id; // Identifier
    char name[64]; // Name of bread type
    int nb; // Number of breads of this type
};

struct TypeList {
  struct BreadType** types; // dynamic array
  int max;  // max number of dynamic types supported (todo: grow automatically)
  int count;    // current number of different types
  int* Sold;    // Types sold in the last k TICKS
  int* TgtgBasket; // Types that are currently offered over TGTG
};

struct TypeList dynTypes;

void initTypeList(int max) {
    dynTypes.max = max;
    dynTypes.count = 0;
    dynTypes.types = (struct BreadType**) malloc(sizeof(struct BreadType*) * max);
    dynTypes.Sold = (int*) malloc(sizeof(int) * max);
    dynTypes.TgtgBasket = (int*) malloc(sizeof(int) * max);
}

void addType(const char* name, int nb) {
    if(dynTypes.max == dynTypes.count) {
        return;
    }
    struct BreadType* bt = (struct BreadType*) malloc(sizeof(struct BreadType));
    strcpy(bt->name, name);
    bt->id = dynTypes.count;
    bt->nb = nb;
    dynTypes.types[dynTypes.count] = bt;
    dynTypes.Sold[dynTypes.count] = NO;
    dynTypes.TgtgBasket[dynTypes.count] = NO;
    dynTypes.count++;
}

void printTypes() {
    for(int i = 0; i < dynTypes.count; i++) {
        struct BreadType* bt = dynTypes.types[i];
        printf("BreadType %d: %s nb: %d\n", i, bt->name, bt->nb);
    }
}

// Types of bread the bakery offers
//struct BreadType types[BREAD_TYPES];

// Types sold in the last k TICKS
//int Sold[BREAD_TYPES];

// Types that are currently offered over TGTG
//int TgtgBasket[BREAD_TYPES];

// Function that gets called every k TICKS and decides whether a bread type is going to be offered via TGTG
void tgtg(){
    for (int i = 0; i < dynTypes.count; i++){
        if (dynTypes.TgtgBasket[i] == NO){
            if (dynTypes.Sold[i] == YES) {
                dynTypes.TgtgBasket[i]= YES;
                printf("%s was flagged for TGTG\n", dynTypes.types[i]->name);
            }
        }
        dynTypes.Sold[i] = NO;
    }
}


int main(){
    // Create bread types dynamically
    initTypeList(10);
    addType("Hartbrot", 4);
    addType("Ruchbrot", 10);
    addType("Muetschli", 5);
    addType("Croissant", 4);
    addType("Zopf", 4);
    addType("Tessinerli", 4);
    addType("Pumpernikel", 4);
    printTypes(); // print types

    // (0) Initialization
    /*for (int i = 0; i < BREAD_TYPES; i++){
        Sold[i] = NO;
        TgtgBasket[i] = NO;
    }*/

    //(1) Create bread
  /*  strcpy(types[CROISSANT].name, "Croissant");
    types[CROISSANT].nb = 4;

    strcpy(types[ZOPF].name, "Zopf");
    types[ZOPF].nb = 4;

    strcpy(types[TESSINERLI].name, "Tessinerli");
    types[TESSINERLI].nb = 4;

    strcpy(types[BURLI].name, "Bürli");
    types[BURLI].nb = 4;

    strcpy(types[PUMPERNIKEL].name, "Pumpernikel");
    types[PUMPERNIKEL].nb = 4;*/
        
            
    //(2) Sell bread
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
                 
    return 0;
}


