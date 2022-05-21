#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

#define NO 0
#define YES 1

/**
 * @brief Initialize a new Type list. The supported number
 * of different types is fixed by parameter max.
 * @param max 
 */
void initTypeList(int max) {
    dynTypes.max = max;
    dynTypes.count = 0;
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