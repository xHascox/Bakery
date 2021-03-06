#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "toogood.h"

// TODO (Lukas) Move BREADS_SOLD and TICKS to CLI
#define BREADS_SOLD 20
#define TICKS 5 // Number of ticks before tgtg check

#define NO 0
#define YES 1

struct TypeList dynTypes;

struct TypeList {
  struct BreadType** types; // dynamic array
  int max;          // max number of dynamic types supported (todo: grow automatically)
  int count;        // current number of different types
  int* Sold;        // Types sold in the last k TICKS
  int* TgtgBasket;  // Types that are currently offered over TGTG
};

// Blueprint for different types of breads
struct BreadType {
    int id;         // Identifier
    char name[64];  // Name of bread type
    int nb;         // Number of breads of this type
};

/**
 * @brief Initialize a new Type list. The supported number
 * of different types is fixed by parameter max.
 * @param max 
 */
void initTypeList(int max) {
    dynTypes.max = max;
    dynTypes.count = 0;
    dynTypes.types = (struct BreadType**) malloc(sizeof(struct BreadType*) * max);
    dynTypes.types = (struct BreadType**) malloc(sizeof(struct BreadType*) * max);
    dynTypes.Sold = (int*) malloc(sizeof(int) * max);
    dynTypes.TgtgBasket = (int*) malloc(sizeof(int) * max);
}

/**
 * @brief Add a new bread-type with passed name 
 * and the passed amount of this bread-type.
 * If the underlying type-list has reached maximum
 * of supported types, the addType request is ignored.
 * @param name 
 * @param nb 
 */
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

/**
 * @brief Just a helper to print all registered bread-types.
 */
void printTypes() {
    for(int i = 0; i < dynTypes.count; i++) {
        struct BreadType* bt = dynTypes.types[i];
        printf("BreadType %d: %s nb: %d\n", i, bt->name, bt->nb);
    }
}

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

void runTGTG(char** breadTypes, int nbTypes, int* amounts, int breadsSold, int ticks) {

    /* Create bread types according to user input */
    initTypeList(nbTypes);
    for(int i = 0; i < nbTypes; i++){
        addType(breadTypes[i], amounts[i]);
    }
    
    /* Sell bread */
    srand(time(NULL));
    int type = 0;

    for (int i=1; i <= breadsSold; i++) {
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


// int main(int argc, char const *argv[]){
//     char* breadtypes[] = {"Croissant", "Zopf", "Tessinerli"};
//     int num[3] = {8,9,10}; 
//     runTGTG(breadtypes,3,num, 20, 4);
// }

